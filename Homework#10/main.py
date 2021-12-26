import numpy as np
import cv2
from PIL import Image
from matplotlib import pyplot as plt

#global Variable
sigma = 1.0

img1 = Image.open("left.jpg")
img2 = Image.open("right.jpg")

img1_resize = img1.resize((int(img1.width / 8), int(img1.height / 8)), Image.LANCZOS)
img1_resize.save('resizedLeft.png', 'png')

img2_resize = img2.resize((int(img2.width / 8), int(img2.height / 8)), Image.LANCZOS)
img2_resize.save('resizedRight.png', 'png')

leftImg = cv2.imread('resizedLeft.png')
rightImg = cv2.imread('resizedRight.png')



def getMatchedKey(leftImg, rightImg):
    gray1 = cv2.cvtColor(leftImg, cv2.COLOR_BGR2GRAY)
    gray2 = cv2.cvtColor(rightImg, cv2.COLOR_BGR2GRAY)

    detector = cv2.ORB_create()

    kp1, desc1 = detector.detectAndCompute(gray1, None)
    kp2, desc2 = detector.detectAndCompute(gray2, None)

    matcher = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=True)

    matches = matcher.match(desc1, desc2)
    # matches = sorted(matches, key=lambda x:x.distance)

    left = []
    right = []

    for i in range(len(matches)):
        left.append(kp1[matches[i].queryIdx].pt)
        right.append(kp2[matches[i].trainIdx].pt)

    return left, right

left, right = getMatchedKey(leftImg, rightImg)


def f(d, e, x, y):
    return d * x + e * y + 1


def g(a, b, c, x, y):
    return a * x + b * y + c


def partialA(a, b, c, d, e, x, y):
    return x / f(a, b, x, y)


def partialB(a, b, c, d, e, x, y):
    return y / f(a, b, x, y)


def partialC(a, b, c, d, e, x, y):
    return 1 / f(a, b, x, y)


def partialD(a, b, c, d, e, x, y):
    return -x * g(a, b, c, x, y) / (f(a, b, x, y) ** 2)


def partialE(a, b, c, d, e, x, y):
    return -y * g(a, b, c, x, y) / (f(a, b, x, y) ** 2)


partialDiff = [partialA, partialB, partialC, partialD, partialE]


def sumOfDiff(i, j, a, b, c, d, e, left, right):
    ans = 0.0
    for inx in range(len(left)):
        ans += partialDiff[i](a, b, c, d, e, left[idx][0], left[idx][1]) * partialDiff[j](a, b, c, d, e, right[idx][0], right[idx][1])
    return ans * 2 / (sigma ** 2)

def hessian(a11, a12, a13, a21, a22, a23, a31, a32, left, right):
    Hx = np.array([[.0 for _ in range(5)] for __ in range(5)])
    Hy = np.array([[.0 for _ in range(5)] for __ in range(5)])

    for i in range(5):
        for j in range(5):
            Hx[i][j] = sumOfDiff(i, j, a11, a12, a13, a31, a32, left, right)
            Hy[i][j] = sumOfDiff(i, j, a21, a22, a23, a31, a32, left, right)
    return Hx, Hy

def gradient(a11, a12, a13, a21, a22, a23, a31, a32, left, right):
    xGradient = np.array([.0 for _ in range(5)], 'float64')
    yGradient = np.array([.0 for _ in range(5)], 'float64')

    for i in range(len(left)):
        leftX = left[i][0]
        leftY = left[i][1]
        rightX = right[i][0]
        rightY = right[i][1]

        ff = f(a31, a32, leftX, leftY)
        g1 = g(a11, a12, a12, leftX, leftY)
        g2 = g(a21, a22, a23, leftX, leftY)

        dx = rightX - g1 / ff
        dy = rightY - g2 / ff

        for j in range(5):
            xGradient[j] += dx * partialDiff[j](a11, a12, a13, a31, a32, leftX, leftY)
            yGradient[j] += dy * partialDiff[j](a21, a22, a23, a31, a32, leftX, leftY)
        xGradient *= -2
        yGradient *= -2
        xGradient /= (sigma ** 2)
        yGradient /= (sigma ** 2)

        return np.array(xGradient), np.array(yGradient)


def errors(a11, a12, a13, a21, a22, a23, a31, a32, left, right):
    xError = .0
    yError = .0

    for i in range(len(left)):
        leftX = left[i][0]
        leftY = left[i][1]
        rightX = right[i][0]
        rightY = right[i][1]

        ff = f(a31, a32, leftX, leftY)
        g1 = g(a11, a12, a12, leftX, leftY)
        g2 = g(a21, a22, a23, leftX, leftY)

        dx = rightX - g1 / ff
        dy = rightY - g2 / ff
        xError += dx ** 2
        yError += dy ** 2

    xError /= (sigma ** 2)
    yError /= (sigma ** 2)

    return xError, yError


def levenberg_marquardt(a11, a12, a13, a21, a22, a23, a31, a32, left, right):
    mLambda = 1e-3
    cnt = 10

    while cnt > 0:

        while True:
            Hx, Hy = hessian(a11, a12, a13, a21, a22, a23, a31, a32, left, right)
            xGradient, yGradient = gradient(a11, a12, a13, a21, a22, a23, a31, a32, left, right)
            xError, yError = errors(a11, a12, a13, a21, a22, a23, a31, a32, left, right)
            HxInverse = np.linalg.inv(Hx + np.identity(5) * mLambda)
            HyInverse = np.linalg.inv(Hy + np.identity(5) * mLambda)

            # if np.linalg.det(HxInverse) > 1 and np.linalg.det(HyInverse) > 1:
            #     HxInverse /= (np.linalg.det(HxInverse) ** .2)
            #     HyInverse /= (np.linalg.det(HyInverse) ** .2)

            crossX = np.dot(HxInverse, xGradient)
            crossY = np.dot(HyInverse, yGradient)

            na11 = a11 - crossX[0]
            na12 = a12 - crossX[1]
            na13 = a13 - crossX[2]

            na21 = a21 - crossY[0]
            na22 = a22 - crossY[1]
            na23 = a23 - crossY[2]

            na31 = a31 - (crossX[3] + crossY[3]) / 2
            na32 = a32 - (crossX[4] + crossY[4]) / 2

            nxError, nyError = errors(na11, na12, na13, na21, na22, na23, na31, na32, left, right)

            if (nxError + nyError >= xError + yError):
                mLambda *= 10
                if mLambda > 1e20:
                    mLambda = 1e20
                    # print(mLambda)
                    break
            else:
                mLambda /= 10
                a11 = na11
                a12 = na12
                a13 = na13
                a21 = na21
                a22 = na22
                a23 = na23
                a31 = na31
                a32 = na32
                if mLambda < 1e-20:
                    mLambda = 1e-20
                    break

        cnt -= 1
    return a11, a12, a13, a21, a22, a23, a31, a32


x_trans=0.0
y_trans=0.0
for idx in range(len(left)):
    x_trans += right[idx][0]-left[idx][0]
    y_trans += right[idx][1]-left[idx][1]
x_trans /= len(left)
y_trans /= len(left)


a11 = 1.0
a12 = .0
a13 = x_trans
a21 = .0
a22 = 1.0
a23 = y_trans
a31 = .0
a32 = .0

print("a11: ", a11, "a12: ", a12, " a13: ", a13, " a21: ", a21, " a22: ", a22, " a23: ", a23, " a31: ", a31, " a32: ", a32)
a11, a12, a13, a21, a22, a23, a31, a32 = levenberg_marquardt(a11, a12, a13, a21, a22, a23, a31, a32, left, right)
print("a11: ", a11, "a12: ", a12, " a13: ", a13, " a21: ", a21, " a22: ", a22, " a23: ", a23, " a31: ", a31, " a32: ", a32)

gray1 = cv2.cvtColor(leftImg, cv2.COLOR_BGR2GRAY)
gray2 = cv2.cvtColor(rightImg, cv2.COLOR_BGR2GRAY)

detector = cv2.ORB_create()

kp1, desc1 = detector.detectAndCompute(gray1, None)
kp2, desc2 = detector.detectAndCompute(gray2, None)

matcher = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=True)

matches = matcher.match(desc1, desc2)


for idx in range(len(matches)):
    x, y = kp1[matches[idx].queryIdx].pt
    kp2[matches[idx].trainIdx].pt = (g(a11, a12, a13, x, y) / f(a31, a32, x, y), g(a21, a22, a23, x, y) / f(a31, a32, x, y))

result = cv2.drawMatches(leftImg, kp1, rightImg, kp2, matches[:100], None, flags=2)
# plt.figure(figsize=(20, 10))
plt.imshow(result)
plt.show()
plt.imsave("descripter_result.jpg", result)