#include <iostream>
#include <string>

using namespace std;

/// @brief Generates string with random numbers and letters given length
/// @param length The length of string
/// @return The generated string
string generateRandomString(int length)
{
    // Create a string to store the result
    string result = "";
    // Loop for each character we want to generate
    for (int i = 0; i < length; i++)
    {
        // Get a random number between 0 and 35
        int random = rand() % 36;
        // If the number is less than 10, then it is a number
        if (random < 10)
            // Append the number to the result string
            result += (char)(random + 48);
        else
            // Otherwise, append the letter to the result string
            result += (char)(random + 87);
    }
    // Return the result string
    return result;
}

// get the hashcode of a string coding letter by its position in string and its value
int getHashCode(string str)
{
    int hash = 0;
    for (int i = 0; i < str.length(); i++)
    {
        hash = hash * i + str[i];
    }
    return hash;
}

int main()
{
    srand(time(NULL));
    // do the following code 100 times to get the average time

    // create an arrays of times for each length for both methods
    double timesByString[4] = {0, 0, 0, 0};
    double timesByHash[4] = {0, 0, 0, 0};
    int lengthOfTest = 10;

    for (int i = 0; i < lengthOfTest; i++)
    {
        // for lengts from 3 to 6
        for (int length = 3; length <= 6; length++)
        {
            int collisionsByHash = 0;   // int to store the number of collisions by hash
            int collisionsByString = 0; // int to store the number of collisions by string
            int hashCodes[2000];        // int array to store the hashCodes of the 2000 random strings
            string strings[2000];       // string array to store the 2000 random strings

            // generate 2000 random strings
            for (int i = 0; i < 2000; i++)
            {
                string str = generateRandomString(length); // generate a random string
                hashCodes[i] = getHashCode(str);           // get the hashcode of the random string
                strings[i] = str;                          // store the random string in the array
            }

            clock_t start = clock(); // initialize the clock

            for (int i = 0; i < 2000; i++) // iterate through the first 2000 strings
            {
                for (int j = i + 1; j < 2000; j++) // iterate through the rest of the strings
                {
                    if (strings[i] == strings[j]) // compare the strings
                        collisionsByString++;     // increment the collision counter
                }
            }
            clock_t end = clock();                                               // set the stop time
            timesByString[length - 3] += (double)(end - start) / CLOCKS_PER_SEC; // add the time to the array

            // count collisions by hash
            start = clock();
            for (int i = 0; i < 2000; i++)
            {
                for (int j = i + 1; j < 2000; j++)
                {
                    if (hashCodes[i] == hashCodes[j])
                        collisionsByHash++;
                }
            }
            end = clock();
            timesByHash[length - 3] += (double)(end - start) / CLOCKS_PER_SEC;
        }
    }

    // count the average time for each length
    for (int i = 0; i < 4; i++)
    {
        timesByString[i] /= lengthOfTest;
        timesByHash[i] /= lengthOfTest;
    }

    // print the results
    cout << "Average time by string: " << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << "Length " << i + 3 << ": " << timesByString[i] << endl;
    }
    cout << endl;
    cout << "Average time by hash: " << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << "Length " << i + 3 << ": " << timesByHash[i] << endl;
    }
    // cout the perfomanse ratio
    cout << endl;
    cout << "Performance ratio: " << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << "Length " << i + 3 << ": " << timesByString[i] / timesByHash[i] << endl;
    }

    return 0;
}