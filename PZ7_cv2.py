# Instrurctions for running the code:

# Open a terminal window.

# Use the pip command to install the opencv-python library:
# pip install opencv-python

# Use the pip command to install the numpy library (required by opencv-python):
# pip install numpy

# Make sure that you edit the path variable to the path where you saved the images (Right after importing the libraries)

# Save the code in a file with a .py extension, for example image_comparison.py.

# In the terminal, navigate to the directory where you saved the file.
# Run the code using the python command:
# python image_comparison.py

# This will run the code and ask you to select a photo type (a = apple or b = banana).
# Once you have selected a photo type, the code will create Image objects for each selected photo,
# compare the images, and print a table of differences between the images.

import cv2
from math import sqrt
# how to install skimage.metrics
# pip install scikit-image

# Define the path to folder with images
path = "C:\\Users\\kolga\\Downloads\\"

# Define the Image class


class Image:
    # Constructor that takes a filepath as an argument and reads the image data from the file
    # Prints the image dimensions to confirm that the image was loaded
    def __init__(self, filepath):
        self.filepath = filepath
        self.image_data = cv2.imread(filepath)
        print(f"{filepath} dimensions: {self.image_data.shape}")

    # Method to return the image data
    def get_image_data(self):
        return self.image_data

# Compare two images and return the total difference


def compare_images(image1, image2):
    # Calculate the absolute difference between the two images
    diff = cv2.absdiff(image1.get_image_data(), image2.get_image_data())
    # Calculate the total difference
    total_diff = cv2.sumElems(diff)[0]

    # Return the square root of the total difference
    return int(sqrt(total_diff))


def main():
    # Ask the user to select a photo type (apple or banana)
    name = input("Select photo type (a = apple or b = banana): ")

    # Check if the user selected a valid photo type
    if name != "a" and name != "b":
        print("Invalid photo type. Please select a or b.")
        return
    if name == "a":
        name = "apple"
    elif name == "b":
        name = "banana"

    # Create Image objects for each selected photo
    image1 = Image(path + name + "_1.bmp")
    image2 = Image(path + name + "_2.bmp")
    image3 = Image(path + name + "_3.bmp")
    image4 = Image(path + name + "_4.bmp")

    # Compare the images and print a table of differences
    images = [image1, image2, image3, image4]

    print()

    # Print a header for the table
    print("       ", end="")
    for i in range(len(images)):
        print(f"image{i+1}  ", end="")
    print("Avg Diff")

    # Print the differences in a table
    for i in range(len(images)):
        print(f"image{i+1} ", end="")
        for j in range(len(images)):
            # Print the difference between image i and image j
            print(f"{compare_images(images[i], images[j]):<8}", end="")
        # Calculate the average difference between image i and all other images
        avg_diff = sum([compare_images(images[i], images[j])
                       for j in range(len(images))]) / len(images)
        # Print the average difference
        print(avg_diff)

    print()

    # Find the most similar image for each image
    for i in range(len(images)):
        # Set the minimum difference and index to a large number initially
        min_diff = 100000
        min_index = 0
        # Compare image i to each other image
        for j in range(len(images)):
            # Skip comparison if i and j are the same image
            if i == j:
                continue
            # Calculate the difference between image i and image j
            diff = compare_images(images[i], images[j])
            # If the difference is smaller than the current minimum, update the minimum difference and index
            if diff < min_diff:
                min_diff = diff
                min_index = j
        # Print the index of the most similar image to image i
        print(f"{i+1} is most similar to {min_index+1}")

    print()

    # Find the most similar image to all images
    # Set the minimum difference and index to a large number initially
    min_diff = 100000
    min_index = 0
    # Compare each image to all other images
    for i in range(len(images)):
        for j in range(len(images)):
            # Skip comparison if i and j are the same image
            if i == j:
                continue
            # Calculate the difference between image i and image j
            diff = compare_images(images[i], images[j])
            # If the difference is smaller than the current minimum, update the minimum difference and index
            if diff < min_diff:
                min_diff = diff
                min_index = i

    # Print the index of the most similar image to all other images
    print(f"{name}_{min_index+1}.bmp is most similar to all images")


if __name__ == "__main__":
    main()
