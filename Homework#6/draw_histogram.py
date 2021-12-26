import matplotlib.pyplot as plt
import numpy as np

n = [100, 1000, 10000, 100000]

def uniform_hist():
    global index
    index = 1
    for i in n:
        uniform = open("uniform_distribution_" + str(i) + ".txt")
        uniform_dis = np.array([], np.float64)
        while True:
            line = uniform.readline()
            if not line: break
            uniform_dis = np.append(uniform_dis, np.float64(line.rstrip("\n")));
        plt.subplot(2, len(n), index)
        # plt.figure(1, figsize=(3, 3))
        plt.xlabel("x axis")
        plt.ylabel("Probability Density")
        plt.title("Uniform Distribution")
        plt.hist(uniform_dis, 100, density=True, color='mediumslateblue')
        index += 1
        # plt.show()

def gauss_hist():
    global index
    for i in n:
        gauss = open("gauss_distribution_" + str(i) + ".txt")
        gauss_dis = np.array([], np.float64)
        while True:
            line = gauss.readline()
            if not line: break
            gauss_dis = np.append(gauss_dis, np.float64(line.rstrip("\n")));
        # plt.figure(1, figsize=(3, 3))
        plt.subplot(2, len(n), index)
        plt.xlabel("x axis")
        plt.ylabel("Probability Density")
        plt.title("Gauss Distribution")
        plt.hist(gauss_dis, 100, density=True, color='lightcoral')
        # plt.show()
        index += 1

plt.figure(1, figsize=(12, 6))
uniform_hist()
plt.figure(1, figsize=(12, 6))
gauss_hist()
plt.tight_layout()
plt.show()
