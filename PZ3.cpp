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

/// @brief Returns the Hash code of the string by Horner's method
/// @param str String you need a hash code for
/// @return Hash code
int getHashCodeHorner(string str) // Method to return the Horner Hash Code of a given string
{
    int hashCode = 0;                      // Initial result is 0
    for (int i = 0; i < str.length(); i++) // Loop through the string
    {
        hashCode = hashCode * 37 + (int)str[i]; // Multiply the result by 37 and add the ASCII value of the current letter
    }
    return hashCode; // Return the final result
}

int main()
{
    srand(time(NULL));

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
            hashCodes[i] = getHashCodeHorner(str);     // get the hashcode of the random string
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
        clock_t end = clock();                                        // set the stop time
        double timeByString = (double)(end - start) / CLOCKS_PER_SEC; // calculate the time elapsed

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
        double timeByHash = (double)(end - start) / CLOCKS_PER_SEC;

        // print results
        cout << "Length: " << length << endl;
        cout << "Collisions by hash: " << collisionsByHash << " ";
        cout << "Collisions by string: " << collisionsByString << endl;
        cout << "Time by hash: " << timeByHash << " ";
        cout << "Time by string: " << timeByString << endl;
        cout << "Time by hash is " << timeByString / timeByHash << " times faster" << endl;
        cout << endl;
    }

    return 0;
}