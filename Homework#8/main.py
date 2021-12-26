import numpy as np
from PIL import Image

image = Image.open("chris.jpg")
img = np.array(Image.open("chris.jpg"))

def bi_linear(img, m, n):
    height, width, color = img.shape

    hRatio = m / height
    wRatio = n / width

    x = np.tile(np.arange(n), (m, 1)) / wRatio
    y = np.arange(m).repeat(n).reshape(m, -1) / hRatio

    ix = np.minimum(np.int64(np.floor(x)), width - 2)
    iy = np.minimum(np.int64(np.floor(y)), height - 2)

    dx = x - ix
    dy = y - iy

    dx = np.repeat(dx[:, :, np.newaxis], 3, axis=2)
    dy = np.repeat(dy[:, :, np.newaxis], 3, axis=2)

    ans = (1 - dx) * (1 - dy) * img[iy, ix] + dx * (1 - dy) * img[iy, ix + 1] + (1 - dx) * dy * img[iy + 1, ix] + dx * dy * img[iy + 1, ix + 1]

    ans = np.uint8(ans)
    return ans

n, m = map(int, input().split())
out = Image.fromarray(bi_linear(img, m, n))
out.save("result.jpg")