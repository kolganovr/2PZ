#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

class Image
{
public:
    fstream img_src;    // Open the image file
    char *img_data;     // Create a char array to store the image data
    int width, height;  // Define the width and height of the image
    static int img_num; // Define the number of the image

    Image()
    {
        string filename = "apple_" + to_string(img_num) + ".bmp";
        img_src.open(filename);

        // write an error message if the file is not found
        if (!img_src)
        {
            cout << "Error: Image " << filename << " not found!" << endl;
            exit(1);
        }

        // write an error if image didnt load
        if (!img_src.is_open())
        {
            cout << "Image " << filename << " FAILED to load!" << endl;
            return;
        }
        else
            cout << "Image " << filename << " loaded";

        img_num++;

        char *info = new char[54];
        img_src.read(info, 54);

        width = *(int *)&info[18];
        height = *(int *)&info[22];

        img_data = new char[width * height * 3];
        img_src.read(img_data, width * height * 3);

        cout << "   w:" << width << " h:" << height << endl;
    };
    ~Image()
    {
        delete[] img_data;
        img_src.close();
    };
};

int Image::img_num = 1;

// Compute the difference between two images
int diff(Image &img1, Image &img2)
{
    // Initialize the sum of squared differences to zero
    unsigned long int diff = 0;
    // Loop over all pixels in the images
    for (int i = 0; i < img1.width * img1.height * 3; i++)
    {
        // Add the squared difference between the two pixels to the running sum
        diff += (img1.img_data[i] - img2.img_data[i]) *
                (img1.img_data[i] - img2.img_data[i]);
    }
    // Return the average of the squared differences
    return diff / (img1.width * img1.height * 3);
}

int main()
{
    Image img1, img2, img3, img4;

#pragma region print table
    cout << endl;
    cout << "Image difference table:" << endl;
    cout << "           " << "Img1      " << "Img2      " << "Img3      " << "Img4      " << endl;
    cout << "Img1       " << diff(img1, img1) << "         " << diff(img1, img2) << "       " << diff(img1, img3) << "       " << diff(img1, img4) << endl;
    cout << "Img2       " << diff(img2, img1) << "       " << diff(img2, img2) << "         " << diff(img2, img3) << "       " << diff(img2, img4) << endl;
    cout << "Img3       " << diff(img3, img1) << "       " << diff(img3, img2) << "       " << diff(img3, img3) << "         " << diff(img3, img4) << endl;
    cout << "Img4       " << diff(img4, img1) << "       " << diff(img4, img2) << "       " << diff(img4, img3) << "       " << diff(img4, img4) << endl;
    cout << endl;
#pragma endregion

#pragma region print average difference
    // find the average difference of each image and print them
    int avr1, avr2, avr3, avr4;
    avr1 = (diff(img1, img2) + diff(img1, img3) + diff(img1, img4)) / 3;
    avr2 = (diff(img2, img1) + diff(img2, img3) + diff(img2, img4)) / 3;
    avr3 = (diff(img3, img1) + diff(img3, img2) + diff(img3, img4)) / 3;
    avr4 = (diff(img4, img1) + diff(img4, img2) + diff(img4, img3)) / 3;

    cout << "Average difference of each image:" << endl;
    cout << "Img1: " << avr1 << endl;
    cout << "Img2: " << avr2 << endl;
    cout << "Img3: " << avr3 << endl;
    cout << "Img4: " << avr4 << endl;
#pragma endregion

#pragma region print the most similar image
    // find the most similar image to others depends on average value calculated above and print its name
    int min = avr1;
    string min_name = "apple_1.bmp";
    int avr[4] = {avr1, avr2, avr3, avr4};
    string names[4] = {"apple_1.bmp", "apple_2.bmp", "apple_3.bmp", "apple_4.bmp"};
    for (int i = 0; i < 4; i++)
    {
        if (avr[i] < min)
        {
            min = avr[i];
            min_name = names[i];
        }
    }
    cout << "The most similar image to others is " << min_name << endl;
#pragma endregion

    return 0;
}