#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

void mapFunc()
{
    // Create a map to store the string counts
    map<string, int> counts;

    // Read the input string
    string input;
    getline(cin, input);

    // Split the input string into individual words
    string word;
    for (const auto &c : input)
    {
        if (c == ' ')
        {
            // Add the word to the map
            ++counts[word];

            // Clear the word
            word.clear();
        }
        else
        {
            // Add the character to the word
            word += c;
        }
    }

    // Print the count for each word
    for (const auto &words : counts)
    {
        cout << words.first << ": " << words.second << endl;
    }
}

int main()
{
    mapFunc();
    return 0;
}
