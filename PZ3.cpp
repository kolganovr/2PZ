#include <iostream>
#include <string>

using namespace std;

// generate random strings of small letters and numbers with given length
string generateRandomString(int length)
{
    string result = "";
    for (int i = 0; i < length; i++)
    {
        int random = rand() % 36;
        if (random < 10)
            result += (char)(random + 48);
        else
            result += (char)(random + 87);
    }
    return result;
}

// generate hash-code of string by Horner's method
int getHashCodeHorner(string str)
{
    int result = 0;
    for (int i = 0; i < str.length(); i++)
    {
        result = result * 37 + (int)str[i];
    }
    return result;
}

int main()
{
    srand(time(NULL));

    // for lengts from 3 to 6
    for (int length = 3; length <= 6; length++)
    {
        int collisionsByHash = 0;
        int collisionsByString = 0;
        int hashCodes[2000];
        string strings[2000];

        // generate 2000 random strings
        for (int i = 0; i < 2000; i++)
        {
            string str = generateRandomString(length);
            hashCodes[i] = getHashCodeHorner(str);
            strings[i] = str;
        }

        clock_t start = clock();
        for (int i = 0; i < 2000; i++)
        {
            for (int j = i + 1; j < 2000; j++)
            {
                if (strings[i] == strings[j])
                    collisionsByString++;
            }
        }
        clock_t end = clock();
        double timeByString = (double)(end - start) / CLOCKS_PER_SEC;

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