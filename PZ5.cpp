#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// This is a struct that stores information about a person
struct Person
{
    string name; // The name of the person
    int age; // The age of the person
    float height; // The height of the person in meters
    bool isMale; // Gender of the person. true = male, false = female
};

vector<Person> readObjectsFromFile(const string &fileName)
{
    vector<Person> objects;

    ifstream file(fileName);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << fileName << endl;
        return objects;
    }

    while (true)
    {
        Person object;
        file >> object.age >> object.height >> object.name >> object.isMale;
        if (!file)
            break;
        objects.push_back(object);
    }

    return objects;
}

void writeObjectsToFile(const string &fileName, const vector<Person> &objects)
{
    ofstream file(fileName);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }

    for (const Person &object : objects)
    {
        file << object.age << " " << object.height << " " << object.name << " " << object.isMale << endl;
    }
}

vector<Person> searchObjects(const vector<Person> &objects, const string &criteria, const string &value)
{
    vector<Person> results;
    for (const Person &object : objects)
    {
        if (criteria == "age")
        {
            if (object.age == stoi(value))
            {
                results.push_back(object);
            }
        }
        else if (criteria == "height")
        {
            if (object.height == stof(value))
            {
                results.push_back(object);
            }
        }
        else if (criteria == "name")
        {
            if (object.name == value)
            {
                results.push_back(object);
            }
        }
        else if (criteria == "isMale")
        {
            if (object.isMale == (value == "true"))
            {
                results.push_back(object);
            }
        }
    }
    return results;
}

int main()
{
    string fileName;
    cout << "Enter the name of the file to store the objects: ";
    cin >> fileName;
    fileName += ".txt";

    // ask the user to create objects or to read them from the file
    string answer;
    cout << "Do you want to create new objects or to read them from the file? (create/read): ";
    cin >> answer;

    // create objects
    if (answer == "create")
    {
        vector<Person> objects;
        while (true)
        {
            Person object;
            cout << "Enter the age: ";
            cin >> object.age;
            cout << "Enter the height in meters: ";
            cin >> object.height;
            cout << "Enter the name: ";
            cin >> object.name;
            cout << "Enter the gender (M/F): ";
            cin >> answer;
            if (answer == "M")
            {
                object.isMale = true;
            }
            else
            {
                object.isMale = false;
            }

            objects.push_back(object);

            cout << "Do you want to add another object? (y/n): ";
            cin >> answer;
            if (answer != "y")
            {
                break;
            }
        }

        writeObjectsToFile(fileName, objects);
    }

    // Read the objects from the file
    vector<Person> objects = readObjectsFromFile(fileName);

    // Perform search and display results
    while (true)
    {
        string criteria;
        string value;
        cout << "Enter search criteria (age, height, name, isMale) or 'all', 'reset' or 'exit': ";
        cin >> criteria;

        if (criteria == "all")
        {
            cout << "Found " << objects.size() << " objects:" << endl;
            for (const Person &object : objects)
            {
                string isMale = object.isMale ? "true" : "false";
                cout << object.age << " " << object.height << " " << object.name << " " << isMale << endl;
            }
            continue;
        }
        else if (criteria == "reset")
        {
            objects = readObjectsFromFile(fileName);
            continue;
        }
        else if (criteria == "exit")
        {
            break;
        }

        cout << "Enter search value: ";
        cin >> value;

        vector<Person> results = searchObjects(objects, criteria, value);

        if (results.empty())
        {
            cout << "No objects found." << endl;
        }
        else
        {
            cout << "Found " << results.size() << " objects:" << endl;
            for (const Person &object : results)
            {
                string isMale = object.isMale ? "true" : "false";
                cout << object.age << " " << object.height << " " << object.name << " " << isMale << endl;
            }
        }

        // Update the list of objects for future searches
        objects = results;
    }

    return 0;
}
