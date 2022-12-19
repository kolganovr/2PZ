#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// This is a struct that stores information about a person
struct Person
{
    string name;  // The name of the person
    int age;      // The age of the person
    float height; // The height of the person in meters
    bool isMale;  // Gender of the person. true = male, false = female
};

// This function reads people's info from a file and returns them as a vector
vector<Person> readObjectsFromFile(const string &fileName)
{
    vector<Person> objects; // create an empty vector of objects

    ifstream file(fileName); // open the file
    if (!file.is_open())     // if the file is not open
    {
        cerr << "Error opening file: " << fileName << endl; // output an error message
        return objects;                                     // return the empty vector
    }

    while (true) // repeat for each object in the file
    {
        Person object;                                                       // create an empty object
        file >> object.age >> object.height >> object.name >> object.isMale; // read the object from the file
        if (!file)                                                           // if the file is not open
            break;                                                           // exit the loop
        objects.push_back(object);                                           // add the object to the vector
    }

    return objects; // return the vector
}

void writeObjectsToFile(const string &fileName, const vector<Person> &objects)
{
    // Open file
    ofstream file(fileName);
    // Check that the file was opened successfully
    if (!file.is_open())
    {
        // Print an error message to cerr
        cerr << "Error opening file: " << fileName << endl;
        return;
    }

    // Write each person to the file
    for (const Person &object : objects)
    {
        file << object.age << " " << object.height << " " << object.name << " " << object.isMale << endl;
    }
}

// This function searches for objects that match the search criteria and returns them as a vector
vector<Person> searchObjects(const vector<Person> &objects, const string &criteria, const string &value)
{
    // Create a vector of Person objects called results
    vector<Person> results;

    // Loop through every object in objects
    for (const Person &object : objects)
    {
        // If the search criteria is age
        if (criteria == "age")
        {
            // If the age of the current object matches the value of age
            if (object.age == stoi(value))
            {
                // Add the current object to the results vector
                results.push_back(object);
            }
        }
        // If the search criteria is height
        else if (criteria == "height")
        {
            // If the height of the current object matches the value of height
            if (object.height == stof(value))
            {
                // Add the current object to the results vector
                results.push_back(object);
            }
        }
        // If the search criteria is name
        else if (criteria == "name")
        {
            // If the name of the current object matches the value of name
            if (object.name == value)
            {
                // Add the current object to the results vector
                results.push_back(object);
            }
        }
        // If the search criteria is isMale
        else if (criteria == "isMale")
        {
            // If the isMale of the current object matches the value of isMale
            if (object.isMale == (value == "true"))
            {
                // Add the current object to the results vector
                results.push_back(object);
            }
        }
    }
    // Return the results vector
    return results;
}

int main()
{
    // declare variable to store file name
    string fileName;
    // prompt user for file name
    cout << "Enter the name of the file to store the objects: ";
    cin >> fileName;
    // add .txt to file name
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

        // Check if the search criteria is "all"
        if (criteria == "all")
        {
            // If it is, print the number of objects found and display all objects
            cout << "Found " << objects.size() << " objects:" << endl;
            for (const Person &object : objects)
            {
                // Convert the gender to a string for display
                string isMale = object.isMale ? "true" : "false";
                // Print the object's information
                cout << object.age << " " << object.height << " " << object.name << " " << isMale << endl;
            }
            // Skip the rest of the loop and go back to the beginning
            continue;
        }
        else if (criteria == "reset")
        {
            // If the search criteria is "reset", read the objects from the file again
            objects = readObjectsFromFile(fileName);
            continue;
        }
        else if (criteria == "exit")
        {
            break;
        }

        // Ask the user for a value to search for
        cout << "Enter search value: ";
        cin >> value;

        // Search for objects matching the criteria
        vector<Person> results = searchObjects(objects, criteria, value);

        // If no objects were found, display a message
        if (results.empty())
        {
            cout << "No objects found." << endl;
        }
        else
        {
            // Display the number of objects found
            cout << "Found " << results.size() << " objects:" << endl;

            // Display each object in the results
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
