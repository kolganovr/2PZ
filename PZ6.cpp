#include <iostream>

using namespace std;

// class of bidirectional list
class List
{
private:
    struct Node
    {
        int id;             // the id of the node
        int data;           // the data of the node
        int accesCount = 0; // the amount of times the node has been accessed
        Node *next;         // the next node in the list
        Node *prev;         // the previous node in the list
    };
    Node *head;        // The head of the doubly-linked list
    Node *tail;        // The tail of the doubly-linked list
    int size;          // The number of nodes in the list
    int currentId = 0; // The current ID to give a new node

public:
    List()
    {
        head = NULL;
        tail = NULL;
        size = 0;
    }
    ~List()
    {
        Node *temp = head;
        while (temp != NULL)
        {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    /// @brief Get node data by its id
    /// @param id id of the element
    /// @return data
    int getbyid(int id)
    {
        // if the id is less than 0, throw an error
        if (id < 0)
        {
            throw "ID cannot be less than 0";
        }

        // declare a pointer to a Node and set it equal to head
        Node *temp = head;
        // while the pointer to a Node is not null
        while (temp != NULL)
        {
            // if the id of the Node is equal to the parameter
            if (temp->id == id)
            {
                // increment the accessCount of the Node
                temp->accesCount++;
                // return the data of the Node
                return temp->data;
            }
            // set the pointer to a Node equal to the next Node
            temp = temp->next;
        }
        // if nothing is found, return -1
        return -1;
    }

    /// @brief Get node data by its positon in the list
    /// @param pos position of the element
    /// @return data
    int getbypos(int pos)
    {
        // declare a pointer to a Node and set it equal to head
        Node *temp = head;
        // while the pointer to a Node is not null
        for (int i = 0; i != pos + 1; i++)
        {
            // if the id of the Node is equal to the parameter
            if (i == pos)
            {
                // increment the accessCount of the Node
                temp->accesCount++;
                // return the data of the Node
                return temp->data;
            }
            // set the pointer to a Node equal to the next Node
            temp = temp->next;
        }
        // if nothing is found, return -1
        return -1;
    }

    /// @brief Ads the element to the end of the list
    /// @param data element value
    void push_back(int data)
    {
        Node *temp = new Node;
        temp->data = data;
        temp->id = currentId;
        temp->next = NULL;
        temp->prev = tail;
        if (tail != NULL)
            tail->next = temp;
        tail = temp;
        if (head == NULL)
            head = temp;
        size++;
        currentId++;
        sort();
    }

    /// @brief Ads the element to the start of the list
    /// @param data element value
    void push_front(int data)
    {
        Node *temp = new Node;
        temp->data = data;
        temp->id = currentId;
        temp->next = head;
        temp->prev = NULL;
        if (head != NULL)
            head->prev = temp;
        head = temp;
        if (tail == NULL)
            tail = temp;
        size++;
        currentId++;
    }

    /// @brief Removes the element from the end of the list
    void pop_back()
    {
        if (tail != NULL)
        {
            Node *temp = tail;
            tail = tail->prev;
            if (tail != NULL)
                tail->next = NULL;
            else
                head = NULL;
            delete temp;
            size--;
        }
    }

    /// @brief Removes the element from the start of the list
    void pop_front()
    {
        if (head != NULL)
        {
            Node *temp = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            else
                tail = NULL;
            delete temp;
            size--;
        }
    }

    /// @brief Insert the element to a given position
    /// @param index where to insert the elemet
    /// @param data value of the element
    void insert(int index, int data)
    {
        if (index < 0 || index > size)
            return;
        if (index == 0)
        {
            push_front(data);
            return;
        }
        if (index == size)
        {
            push_back(data);
            return;
        }
        Node *temp = head;
        for (int i = 0; i < index; i++)
            temp = temp->next;
        Node *newNode = new Node;
        newNode->data = data;
        newNode->id = currentId;
        newNode->next = temp;
        newNode->prev = temp->prev;
        temp->prev->next = newNode;
        temp->prev = newNode;
        size++;
        currentId++;
    }

    /// @brief Removes the element from a given position
    /// @param index where to remove the element
    void eraseElem(int index)
    {
        if (index < 0 || index >= size)
            return;
        if (index == 0) // if index is 0, delete the first element
        {
            pop_front();
            return;
        }
        if (index == size - 1) // if index is last element, delete it
        {
            pop_back();
            return;
        }
        Node *temp = head;              // create a temp Node
        for (int i = 0; i < index; i++) // iterate through the list until you reach the index
            temp = temp->next;
        temp->prev->next = temp->next; // link the previous to the next
        temp->next->prev = temp->prev; // link the next to the previous
        delete temp;                   // delete the node at the index
        size--;                        // decrease the size
    }

    // print the list in format: id accesCount data
    void print()
    {
        Node *temp = head;
        cout << "id AC data" << endl;
        while (temp != NULL)
        {
            cout << temp->id << " " << temp->accesCount << " " << temp->data << endl;
            temp = temp->next;
        }
    }

    // sort the list based on accesCount
    void sort()
    {
        Node *temp = head;
        Node *temp2 = head;
        while (temp != NULL)
        {
            while (temp2 != NULL)
            {
                if (temp->accesCount > temp2->accesCount)
                {
                    int tempData = temp->data;
                    int tempId = temp->id;
                    int tempAccesCount = temp->accesCount;
                    temp->data = temp2->data;
                    temp->id = temp2->id;
                    temp->accesCount = temp2->accesCount;
                    temp2->data = tempData;
                    temp2->id = tempId;
                    temp2->accesCount = tempAccesCount;
                }
                temp2 = temp2->next;
            }
            temp2 = temp;
            temp = temp->next;
        }
    }
};

int main()
{
    // create a list
    List list;
    // add elements to the list
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_front(-10);

    list.print();

    cout << list.getbypos(2) << endl;
    cout << list.getbypos(2) << endl;
    cout << list.getbypos(3) << endl;
    cout << list.getbyid(4) << endl;

    list.sort();
    list.print();
}
