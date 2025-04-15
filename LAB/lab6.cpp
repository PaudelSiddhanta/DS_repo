/*
 * @file	lab6.cpp
 * @author	Siddhanta Paudel
 * @description Binary Heap Implementation in C++
 * @date	7 June 2024
 */
// starter_code_begins
#include <iostream>
#include <exception>
#include <math.h>
#include <ctime>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

class Heap
{
private:
	vector<int> array;

public:
	Heap();
	void insert(int key);
	int removeMin();
	int getMin();
	int parent(int k);
	int left(int k);
	int right(int k);
	void bubbleup(int k);
	void bubbledown(int k);
	void print();
	void sort();
};

void listCommands()
{
	cout << "-----------------------------------------------------------------" << endl;
	cout << "display            :Display the Heap" << endl
		 << "insert <key>       :Insert a new element in the Heap" << endl
		 << "getMin             :Get the element with Min. Key in the Heap" << endl
		 << "removeMin          :Remove the element with Min. Key from Heap" << endl
		 << "sort               :Sort the Heap" << endl
		 << "help               :Display the available commands" << endl
		 << "exit/quit          :Exit the program" << endl;
	cout << "-----------------------------------------------------------------" << endl;
}
//=============================================
void demo(Heap &myHeap)
{
	for (int i = 1; i <= 7; i++)
	{
		int n = rand() % 25;
		myHeap.insert(n);
	}
	myHeap.print();
}
//=============================================
int main()
{

	Heap myHeap;
	string user_input;
	string command;
	string argument;

	listCommands();

	while (true)
	{
		try
		{
			cout << ">";
			getline(cin, user_input);

			// parse userinput into command and parameter(s)
			stringstream sstr(user_input);
			getline(sstr, command, ' ');
			getline(sstr, argument);

			if (command == "display" or command == "d")
				myHeap.print();
			else if (command == "insert" or command == "i")
			{
				myHeap.insert(stoi(argument));
				myHeap.print();
			}
			else if (command == "getMin")
			{
				int min = myHeap.getMin();
				cout << "Min Key = " << min << endl;
			}
			else if (command == "removeMin" or command == "r")
			{
				cout << myHeap.removeMin() << " has been removed..!" << endl;
				myHeap.print();
			}
			else if (command == "sort")
			{
				myHeap.sort();
				myHeap.print();
			}
			else if (command == "help")
				listCommands();
			else if (command == "demo")
				demo(myHeap);
			else if (command == "exit" or command == "quit")
				break;
			else
				cout << "Invalid command !!!" << endl;
		}
		catch (exception &e)
		{
			cout << "Exception: " << e.what() << endl;
		}
	}
	return EXIT_SUCCESS;
}
//==================================================================
// This method prints a Heap in 2D format.
void Heap::print()
{
	if (array.size() > 1)
	{
		int levels = int(log2(array.size()));

		int *spaces = new int[levels + 1];
		spaces[levels] = 0;

		for (int j = levels - 1; j >= 0; j--)
		{
			spaces[j] = 2 * spaces[j + 1] + 1;
		}

		int level = 0;
		for (int i = 0; i < array.size() - 1; i++)
		{
			if (i == (pow(2, level) - 1))
			{
				cout << endl
					 << endl;

				for (int k = 0; k < spaces[level]; k++)
					cout << "   ";
				level++;
			}
			cout << std::left << setw(3) << array[i + 1];

			if (level > 1)
			{
				for (int k = 0; k < spaces[level - 2]; k++)
					cout << "   ";
			}
		}
		cout << endl;
		for (int i = 0; i < spaces[0] * log2(array.size() / 2) + 4; i++)
			cout << "__";

		cout << endl;
		delete[] spaces;
	}
}
// starter_code_ends
// Constructor
Heap::Heap()
{
	// to-do
	array.push_back(INT_MIN);
}
// Insert an element in Heap keeping the Heap property intact
void Heap::insert(int key)
{
	// to-do
	array.push_back(key);
	int size = array.size() - 1;
	bubbleup(size);
}
// Remove the minimum value from Heap keeping the Heap property intact
int Heap::removeMin()
{
	// to-do
	int size = array.size() - 1; // find the size of heap
	int temp = array[1];		 // assign a template variable to the top element(minimum)
	array[1] = array[size];		 // assign the last element to the top part  ...doing this destroys the heap structure
	array.pop_back();			 // remove the last element
	bubbledown(1);				 // bubbledown the top element
	return (temp);				 // return the element stored in top(previously the minimum of the heap)
}
// Return (but don't remove) the minimum value from the Heap
int Heap::getMin()
{
	// to-do
	return array[1]; // return the first value of heap
}
// Returns the index of the parent of the node i
int Heap::parent(int k)
{
	// to-do
	return k / 2;
}
// Returns the index of the left child of the node i
int Heap::left(int k)
{
	// to-do
	return 2 * k;
}
// Returns the index of the right child of the node i
int Heap::right(int k)
{
	// to-do
	return 2 * k + 1;
}

void Heap::bubbleup(int k)
{
	// to-do
	int temp;
	while (array[parent(k)] > array[k]) // while the parent is larger than child, swap parent child and update the current index child to that of parent
	{
		temp = array[k]; // swap
		array[k] = array[parent(k)];
		array[parent(k)] = temp;
		k = parent(k); // update index
	}
}

void Heap::bubbledown(int k)
{
	int temp;
	int size = array.size() - 1;
	while (true)
	{ // if it has no children, don't do anything
		if (left(k) > size && right(k) > size)
		{
			return;
		}
		else if (left(k) <= size && right(k) > size)
		{ // if there is only left node and no right node, compare with the left child and swap if necessary
			if (array[k] > array[left(k)])
			{
				temp = array[k];
				array[k] = array[left(k)];
				array[left(k)] = temp;
				return;
			}
			else // just for maintaining the structure
			{
				return;
			}
		}
		else if (left(k) <= size && right(k) <= size)								   // if the node has both left and right child
		{																			   // find the smaller child and swap
			int small_index = (array[left(k)] < array[right(k)] ? left(k) : right(k)); // assign index of smaller child to small_index
			if (array[k] > array[small_index])										   // perform swapping until the correct order of heap is maintained
			{
				temp = array[k]; // swap
				array[k] = array[small_index];
				array[small_index] = temp;
				k = small_index; // update index
			}
			else
			{
				return; // if the if condition doesn't satisfy, just return
			}
		}
	}
}
//=====================================
// This method will sort the internal array/vector
// Hint: Leep extracting the min value from the heap and store them into an auxiliary array.
//       Copy the values from auxiliary array to the internal array/vector of heap
void Heap::sort()
{
	// to-do
	vector<int> temp;		 // create a temporary vector
	//int size = array.size(); // size variable used as counter
	while (array.size() != 1)		 // until all elements of the heap are removed and transferred
	{
		temp.push_back(removeMin()); // remove the minimum element from the heap and insert it in the temporary vector
		//size--;						 // decrease the size count
	}
	vector<int>::iterator it; // define an iterator
	while (!temp.empty())	  // until the temporary vector is empty
	{
		array.push_back(temp.front()); // insert the elements of temp to the heap
		it = temp.begin();			   // update the iterator to point to the front
		temp.erase(it);				   // erase the front element of the vector
	}
}
//=============================================