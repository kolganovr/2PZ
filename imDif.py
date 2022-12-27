import cv2
import numpy as np
import matplotlib.pyplot as plt

# Load images
img1_c = cv2.imread("C:\\Users\\kolga\\Downloads\\apple_1.bmp")
img2_c = cv2.imread("C:\\Users\\kolga\\Downloads\\apple_2.bmp")
img3_c = cv2.imread("C:\\Users\\kolga\\Downloads\\apple_3.bmp")
img4_c = cv2.imread("C:\\Users\\kolga\\Downloads\\apple_4.bmp")

# Convert images to grayscale
img1 = cv2.cvtColor(img1_c, cv2.COLOR_BGR2GRAY)
img2 = cv2.cvtColor(img2_c, cv2.COLOR_BGR2GRAY)
img3 = cv2.cvtColor(img3_c, cv2.COLOR_BGR2GRAY)
img4 = cv2.cvtColor(img4_c, cv2.COLOR_BGR2GRAY)


def error(img1, img2):
    diff = cv2.subtract(img1, img2)
    mse = np.sum(diff ** 2)/(float(img1.shape[0] * img1.shape[1]))
    return mse, diff


def main():
    images = [img1, img2, img3, img4]

    # Print a header for the table
    print("       ", end="")
    for i in range(len(images)):
        print(f"image{i+1}  ", end="")
    print()

    # Print the differences in a table
    for i in range(len(images)):
        print(f"image{i+1} ", end="")
        for j in range(len(images)):
            mse = error(images[i], images[j])[0]
            mse = int(mse*10)/10.0
            print(f"{mse:<8}", end="")
        print()

    # get diffs for each image pair
    mse12, diff12 = error(img1, img2)
    mse13, diff13 = error(img1, img3)
    mse14, diff14 = error(img1, img4)
    mse23, diff23 = error(img2, img3)
    mse24, diff24 = error(img2, img4)
    mse34, diff34 = error(img3, img4)

    # plot diffs
    plt.subplot(2, 3, 1), plt.imshow(
        diff12, cmap='gray'), plt.title(f"Diff 1-2 = {mse12:.1f}")
    plt.subplot(2, 3, 2), plt.imshow(
        diff13, cmap='gray'), plt.title(f"Diff 1-3 = {mse13:.1f}")
    plt.subplot(2, 3, 3), plt.imshow(
        diff14, cmap='gray'), plt.title(f"Diff 1-4 = {mse14:.1f}")
    plt.subplot(2, 3, 4), plt.imshow(
        diff23, cmap='gray'), plt.title(f"Diff 2-3 = {mse23:.1f}")
    plt.subplot(2, 3, 5), plt.imshow(
        diff24, cmap='gray'), plt.title(f"Diff 2-4 = {mse24:.1f}")
    plt.subplot(2, 3, 6), plt.imshow(
        diff34, cmap='gray'), plt.title(f"Diff 3-4 = {mse34:.1f}")

    plt.show()


if __name__ == "__main__":
    main()
