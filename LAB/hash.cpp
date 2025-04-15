//============================================================================
// Name        : Hash Table
// Author      :
// Version     : 1.0
// Date Created:
// Date Modified:
// Description : Hash Table implementation using C++
//============================================================================
// starter-code-begins

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <iomanip>
#include <list>

using namespace std;

class Entry
{
private:
    string key;
    string value;
    bool deleted; // Is the bucket available to be reused (after deletion)
public:
    Entry(string key, string value)
    {
        this->key = key;
        this->value = value;
        this->deleted = false;
    }
    friend class HashTable;
};

class HashTable
{
private:
    Entry **buckets;        // Array of Pointers to Entries
    unsigned int capacity;  // Total Capacity of Hash Table
    unsigned int size;      // Current # of entries in the Hash Table
    unsigned int collisions; // Total Number of Collisions
public:
    HashTable(int capacity);
    unsigned int getSize();
    unsigned int getCollisions();
    unsigned long hashCode(string key);
    void insert(string key, string value);
    void remove(string key);
    string search(string key);
    ~HashTable();
};
//======================================================
int main(void)
{
    ifstream fin;
    fin.open("zipcodes.csv");
    if (!fin)
    {
        cout << "Cannot open the file <zipcodes.csv>...!" << endl;
        exit(-1);
    }

    string line;
    HashTable myHashTable(28859); // Prime number 30% bigger than >25844 (19880*1.3);
    getline(fin, line);           // skip first line
    while (getline(fin, line))
    {
        stringstream ss(line);
        string key, value;
        getline(ss, key, ',');
        getline(ss, value);
        myHashTable.insert(key, value);
    }
    fin.close();

    cout << "===================================================" << endl;
    cout << "Hash Table size = " << myHashTable.getSize() << endl;
    cout << "Total Number of Collisions = " << myHashTable.getCollisions() << endl;
    cout << "Avg. # collisions/entry = " << setprecision(2) << float(myHashTable.getCollisions()) / myHashTable.getSize() << endl;
    cout << "===================================================" << endl;

    string user_input, command, argument1, argument2;

    while (true)
    {
        cout << ">";
        getline(cin, user_input);

        stringstream sstr(user_input);
        getline(sstr, command, ' ');
        getline(sstr, argument1, ',');
        getline(sstr, argument2);

        if (command == "find")
            cout << "Zip code for " << argument1 << " is: " << myHashTable.search(argument1) << endl;
        else if (command == "insert")
            myHashTable.insert(argument1, argument2);
        else if (command == "remove")
            myHashTable.remove(argument1);
        else if (command == "help")
            cout << "Available Commands:\ninsert <key,value>\nremove <key>\nfind <key>" << endl;
        else if (command == "exit")
            break;
        else
            cout << "Invalid command !!!" << endl;
    }
    return 0;
}
//===================================================
HashTable::HashTable(int capacity)
{
    buckets = new Entry *[capacity]; // Array of Pointers to Entries
    for (int i = 0; i < capacity; i++)
        buckets[i] = nullptr;

    this->capacity = capacity;
    this->size = 0;
    this->collisions = 0;
}

//======================================================
// Please add your implementaiton below this line.

unsigned long HashTable::hashCode(string key)
{
    unsigned h = 0;
    int length = key.length();

    for (int i = 0; i < length; i++)
    {
        h += (unsigned int)key[i];
        h = (h << 5 | h >> 27);
    }
    return h % capacity; // compressed hash code
}

void HashTable::insert(string key, string value)
{
    int hash_code = hashCode(key);
    bool inserted = false;
    int i = 1;
    while (!inserted)
    {
        if (buckets[hash_code] == nullptr || buckets[hash_code]->deleted)
        {
            buckets[hash_code] = new Entry(key, value);
            inserted = true;
            size++;
        }
        else if (buckets[hash_code]->key == key && !buckets[hash_code]->deleted)
        {
            buckets[hash_code]->value = value;
            inserted = true;
        }
        else
        {
            hash_code = (hash_code + i * i) % this->capacity;
            i++;
            this->collisions++;
        }
    }
}

unsigned int HashTable::getSize()
{
    return size;
}

unsigned int HashTable::getCollisions()
{
    return collisions;
}

string HashTable::search(string key)
{
    int hash_code = hashCode(key);
    int i = 0;
    while (buckets[hash_code] != nullptr)
    {
        if (buckets[hash_code]->key == key && !buckets[hash_code]->deleted)
        {
            return buckets[hash_code]->value + "     (comparisons = " + to_string(i + 1) + ")";
        }
        else
        {
            hash_code = (hash_code + i * i) % capacity;
            i++;
            if (i >= capacity) // Check for infinite loop
                break;
        }
    }
    return "Record not found!";
}

void HashTable::remove(string key)
{
    int i = 0;
    int hash_code = hashCode(key);
    while (buckets[hash_code] != nullptr)
    {
        if (buckets[hash_code]->key == key)
        {
            if (!buckets[hash_code]->deleted)
            {
                buckets[hash_code]->deleted = true;
                size--;
                return;
            }
            else
            {
                cout << "Record not found" << endl;
                return;
            }
        }
        else
        {
            hash_code = (hash_code + i * i) % capacity;
            i++;
        }
    }
}

HashTable::~HashTable()
{
    for (int i = 0; i < capacity; i++)
        delete buckets[i];
    delete[] buckets;
}
