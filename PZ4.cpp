#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

void mapFunc()
{
    // Create a map to store the string counts
    map<string, int> counts;

    // Read the input string
    cout << "Enter a string containing words separated by spaces: ";
    string input;
    getline(cin, input);

    // Split the input string into individual words
    istringstream iss(input);
    string word;
    while (iss >> word)
    {
        // Remove any punctuation from the word
        if (word[word.length() - 1] == '.' || word[word.length() - 1] == ',' 
        || word[word.length() - 1] == '!' || word[word.length() - 1] == '?' || word[word.length() - 1] == ':')
            word = word.substr(0, word.length() - 1);

        // Add the word to the map
        ++counts[word];
    }

    // Print the count for each word
    for (const auto &words : counts)
    {
        cout << words.first << ": " << words.second << endl;
    }
}

void vectorFunc()
{
    // random seed
    srand(time(NULL));
    // Read the sizes of the two vectors
    cout << "Enter the sizes of the two vectors: ";
    int size1, size2;
    cin >> size1 >> size2;

    // Create the two vectors and fill them with random numbers between -100 and 100
    vector<int> vec1(size1), vec2(size2);
    generate(vec1.begin(), vec1.end(), []() { return rand() % 201 - 100; });
    generate(vec2.begin(), vec2.end(), []() { return rand() % 201 - 100; });

    // Output the contents of the two vectors
    cout << "Vector 1:";
    for (const auto &x : vec1)
        cout << ' ' << x;
    cout << '\n';

    cout << "Vector 2:";
    for (const auto &x : vec2)
        cout << ' ' << x;
    cout << '\n';

    // Find the arithmetic mean of the elements of each vector
    double mean1 = 0, mean2 = 0;
    for (const auto &x : vec1)
        mean1 += x;
    mean1 /= vec1.size();

    for (const auto &x : vec2)
        mean2 += x;
    mean2 /= vec2.size();

    cout << "Mean of vector 1: " << mean1 << '\n';
    cout << "Mean of vector 2: " << mean2 << '\n';

    // Find the intersecting elements of the two vectors
    vector<int> intersect;
    set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(),
                          back_inserter(intersect));

    cout << "Intersecting elements:";
    // if there are no intersecting elements, print "none"
    if (intersect.empty())
        cout << " none";
    else
        for (const auto &x : intersect)
            cout << ' ' << x;
}

int main()
{
    mapFunc();
    vectorFunc();
    
    return 0;
}