#include <iostream>
using namespace std;

class HashTable
{
    int* table;
    int size;

public:

    HashTable(int s)
    {
        size = s;
        table = new int[size];

        for (int i = 0; i < size; i++)
            table[i] = -1;
    }

    ~HashTable()
    {
        delete[] table;
    }

    int hashFunction(int key)
    {
        return key % size;
    }

    void insert(int key)
    {
        int index = hashFunction(key);

        for (int i = 0; i < size; i++)
        {
            int pos = (index + i * i) % size;

            if (table[pos] == -1)
            {
                table[pos] = key;
                return;
            }
        }

        cout << "Table is full\n";
    }

    int search(int key)
    {
        int index = hashFunction(key);

        for (int i = 0; i < size; i++)
        {
            int pos = (index + i * i) % size;

            if (table[pos] == -1)
                return -1;

            if (table[pos] == key)
                return pos;
        }

        return -1;
    }

    void remove(int key)
    {
        int pos = search(key);

        if (pos == -1)
            cout << "Key not found\n";
        else
            table[pos] = -2;
    }

    void display()
    {
        for (int i = 0; i < size; i++)
        {
            cout << i << " : ";

            if (table[i] == -1)
                cout << "EMPTY";
            else if (table[i] == -2)
                cout << "DELETED";
            else
                cout << table[i];

            cout << endl;
        }
    }

    bool isEmpty()
    {
        for (int i = 0; i < size; i++)
        {
            if (table[i] != -1 && table[i] != -2)
                return false;
        }

        return true;
    }

    bool isFull()
    {
        for (int i = 0; i < size; i++)
        {
            if (table[i] == -1 || table[i] == -2)
                return false;
        }

        return true;
    }

    void clear()
    {
        for (int i = 0; i < size; i++)
            table[i] = -1;
    }
};

int main()
{
    HashTable h(10);

    h.insert(25);
    h.insert(35);
    h.insert(15);
    h.insert(20);
    h.insert(30);

    h.display();

    cout << "\nSearch 35: ";

    int pos = h.search(35);

    if (pos != -1)
        cout << "Found at index " << pos;
    else
        cout << "Not Found";

    h.remove(35);

    cout << "\n\nAfter deleting 35:\n";
    h.display();

    return 0;
}