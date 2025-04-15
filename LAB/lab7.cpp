//============================================================================
// Name         : Hash Table
// Author       : Siddhanta Paudel
// Version      : 1.0
// Date Created : 11 June 2024
// Date Modified:
// Description  : Hash Table implementation using C++
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
	Entry **buckets;		 // Array of Pointers to Entries
	unsigned int capacity;	 // Total Capacity of Hash Table
	unsigned int size;		 // Current # of entries in the Hash Table
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
		cout << "Can not open the file <zipcodes.txt>...!" << endl;
		exit(-1);
	}

	string line;
	HashTable myHashTable(28859); // Prime number 30% bigger than >25844 (19880*1.3);
	getline(fin, line);			  // skip first line
	while (!fin.eof())
	{
		string key, value;
		getline(fin, key, ',');
		getline(fin, value);
		// cout<<key<<":"<<value<<endl;
		std::cout.setstate(std::ios_base::failbit); // dont print any thing on terminal until the failbit is cleared again.
		myHashTable.insert(key, value);

		std::cout.clear(); // clear the failbit
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
// starter-code-ends
//======================================================
// Please add your implementaiton below this line.
unsigned long HashTable::hashCode(string key)
{
	int i = 0;
	unsigned h = 0;
	while (key[i] != '\0') // traverse through the entire string
	{					   // cycle shift hash code
		h += (unsigned int)key[i];
		h = (h << 5 | h >> 27); // right shift by 27 and left shift by 5, "OR" the results and add to the hash code
		i++;					// increase the counter
	}
	return h % capacity; // compressed hash code
}
void HashTable::insert(string key, string value)
{
	int hash_code = hashCode(key); // find the hashCode for the key
	bool inserted = false;		   // boolean to check whether the value has been inserted or not
	int i = 0;					   // used for quadratic probing
	while (inserted != true)	   // repeat until the value has been inserted
	{
		if (buckets[hash_code] == nullptr || buckets[hash_code]->deleted) // if the bucket is either null or was previously deleted, elements can be added
		{
			buckets[hash_code] = new Entry(key, value); // dynamically create a new entry and add key value pairs
			cout << "New record has been inserted." << endl;
			inserted = true; // update the flag
			size++;			 // increase the size
		}
		else if (buckets[hash_code]->key == key && !buckets[hash_code]->deleted)
		{									   // if the key matches and the bucket is not deleted, value can be updated in this type of bucket
			buckets[hash_code]->value = value; // update the value
			cout << "Existing record has been updated." << endl;
			inserted = true; // update the flag
		}
		else // if the entry could not be updated, probe for a new bucket using quadratic probing
		{
			hash_code = (hash_code + i * i) % this->capacity;
			i++;
			this->collisions++; // increase the number of collisions
		}
	}
	// cout<<"final position: "<<hash_code<<endl;
}
unsigned int HashTable::getSize() // return the size of the hashtable
{
	return size;
}
unsigned int HashTable::getCollisions() // return the total collisions that happened
{
	return collisions;
}
string HashTable::search(string key) // search for a key value pair in the hash table using key
{
	int hash_code = hashCode(key); // calculate the hash function
	int i = 0;
	while (buckets[hash_code] != nullptr) // repeat until a null bucket is encountered
	{
		if (buckets[hash_code]->key == key && !buckets[hash_code]->deleted)
		{ // if the key matches and the bucket has not been deleted
			return buckets[hash_code]->value + "     (comparisons = " + to_string(i + 1) + ")";
		}
		else
		{ // else search for the next position using quadratic probing
			hash_code = (hash_code + i * i) % capacity;
			i++;
			if (i >= capacity) // Check for infinite loop
				break;
		}
	}
	return "Record not found!"; // if no record s found return message
}
void HashTable::remove(string key) // remove a key value pair from the hash function .... perform a lazy deletion
{
	int i = 0;
	int hash_code = hashCode(key);		  // find the hash code for the key
	while (buckets[hash_code] != nullptr) // repeat until a nullptr is found
	{
		if (buckets[hash_code]->key == key) // if the key is found
		{
			if (buckets[hash_code]->deleted == false) // and it is not a deleted entry
			{
				buckets[hash_code]->deleted = true;											  // convert the flag to deleted
				cout << buckets[hash_code]->key << " has been successfully removed!" << endl; // print the error message
				size--;																		  // reduce the size
				return;
			}
			else
			{ // if the key is found but the record is already deleted, it means that the record is not found
				cout << "Record not found" << endl;
				return;
			}
		}
		else
		{ // perform quadratic probing to move to the next element
			hash_code = (hash_code + i * i) % capacity;
			i++;
		}
	}
	cout<<"Record not found."<<endl;
}
HashTable::~HashTable() // destructor for the hash function
{
	for (int i = 0; i < capacity; i++)
		delete buckets[i]; // delete the individual entries
	delete[] buckets;	   // delete the double pointer
}
