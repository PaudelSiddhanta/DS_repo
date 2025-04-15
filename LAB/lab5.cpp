//============================================================================
// Name         : MyVector.cpp
// Author       : Siddhanta Paudel
// Version      : 1.0
// Date Created : Jun 4, 2024
// Date Modified:
// Description  : Vector implmentation in C++
//============================================================================
// start_code+begins
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <stdexcept>
#include <sstream>
#include <exception>

using namespace std;
// create a new exception class for the case when vector is empty
class VectorEmpty : public exception
{
public:
	virtual const char *what() const throw() // default c++ template
	{
		return "Vector is Empty..";
	}
};

template <typename T>
class MyVector
{
private:
	T *data;		// pointer to int(array) to store elements
	int v_size;		// current size of vector (number of elements in vector)
	int v_capacity; // capacity of vector
public:
	MyVector(int cap = 0);			   // Constructor
	~MyVector();					   // Destructor
	int size() const;				   // Return current size of vector
	int capacity() const;			   // Return capacity of vector
	bool isEmpty() const;			   // Rturn true if the vector is empty, False otherwise
	const T &front();				   // Returns reference of the first element in the vector
	const T &back();				   // Returns reference of the Last element in the vector
	void push_back(T element);		   // Add an element at the end of vector
	void insert(int index, T element); // Add an element at the index
	void erase(int index);			   // Removes an element from the index
	T &operator[](int index);		   // Returns the reference of an element at given index
	T &at(int index);				   // return reference of the element at given index
	void shrink_to_fit();			   // Reduce vector capacity to fit its size
	void display();
	void reserve(int cap); // reserve an array of size cap;
};

void listCommands()
{
	cout << "List of available Commands:" << endl
		 << "display                  : Display the Vector" << endl
		 << "push_back <element>      : Add an element to the end of the vector" << endl
		 << "insert <index element>   : Insert an element at location index" << endl
		 << "erase <index>            : Remove the element from index" << endl
		 << "[index]                  : Returns a reference to an element at a specified index" << endl
		 << "at <index>               : Returns a reference to an element at a specified index" << endl
		 << "front                    : Return the (reference of) front element" << endl
		 << "back                     : Returns a reference to the last element of the vector" << endl
		 << "size                     : Returns the number of elements in the vector" << endl
		 << "capacity                 : Returns the capacity of vector" << endl
		 << "isEmpty                  : Tests if the vector container is empty" << endl
		 << "shrink                   : Reduce vector capacity to fit its size (shrink_to_fit)" << endl
		 << "exit/quit                : Exit the Program" << endl;
}
//=======================================
int main()
{

	MyVector<int> myVector;
	// unitTest();
	string user_input;
	string command;
	string parameter1;
	string parameter2;
	listCommands();

	do
	{
		cout << ">";
		getline(cin, user_input);

		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr, command, ' ');
		getline(sstr, parameter1, ' ');
		getline(sstr, parameter2);

		try
		{
			if (command == "display" or command == "d")
				myVector.display();
			else if (command == "push_back" or command == "p")
				myVector.push_back(stoi(parameter1)), myVector.display();
			else if (command == "insert" or command == "i")
				myVector.insert(stoi(parameter1), stoi(parameter2)), myVector.display();
			else if (command == "erase" or command == "e")
				myVector.erase(stoi(parameter1)), myVector.display();
			else if (command == "at" or command == "a")
				cout << myVector.at(stoi(parameter1)) << endl;
			else if (command[0] == '[' and command[command.length() - 1] == ']')
				cout << myVector[stoi(command.substr(1, command.length() - 2) + "")] << endl;
			else if (command == "front" or command == "f")
				cout << myVector.front() << endl;
			else if (command == "back" or command == "b")
				cout << myVector.back() << endl;
			else if (command == "size" or command == "s")
				cout << myVector.size() << endl;
			else if (command == "capacity" or command == "c")
				cout << myVector.capacity() << endl;
			else if (command == "isEmpty" or command == "ie")
				cout << boolalpha << myVector.isEmpty() << endl;
			else if (command == "shrink")
				myVector.shrink_to_fit(), myVector.display();
			else if (command == "help" or command == "?")
				listCommands();
			else if (command == "exit" or command == "quit")
				break;
			else
				cout << "Invalid Commad !!" << endl;
		}
		catch (exception &e)
		{
			cout << "Exception: " << e.what() << endl;
		}

	} while (command != "exit" and command != "quit");

	return EXIT_SUCCESS;
}
//======================================
#ifndef _WIN32
//======================================
template <typename T>
void MyVector<T>::display()
{
	cout << "╔";

	for (int i = 0; i < v_capacity; i++)
	{
		cout << "════";
		if (i != v_capacity - 1)
			cout << "╦";
	}
	cout << "╗ size = " << v_size << endl;

	for (int i = 0; i < v_capacity; i++)
	{
		cout << "║";
		if (i < v_size)
			cout << setw(4) << data[i];
		else
			cout << setw(4) << " ";
	}
	if (v_capacity == 0)
		cout << "║";
	cout << "║" << endl
		 << "╚";
	for (int i = 0; i < v_capacity; i++)
	{
		cout << "════";
		if (i != v_capacity - 1)
			cout << "╩";
	}
	cout << "╝ capacity = " << v_capacity << endl;
}
//======================================
#else
template <typename T>
void MyVector<T>::display()
{
	cout << "+";

	for (int i = 0; i < v_capacity; i++)
	{
		cout << "----";
		if (i != v_capacity - 1)
			cout << "+";
	}
	cout << "+ size = " << v_size << endl;

	for (int i = 0; i < v_capacity; i++)
	{
		cout << "|";
		if (i < v_size)
			cout << setw(4) << data[i];
		else
			cout << setw(4) << " ";
	}
	if (v_capacity == 0)
		cout << "|";
	cout << "|" << endl
		 << "+";
	for (int i = 0; i < v_capacity; i++)
	{
		cout << "----";
		if (i != v_capacity - 1)
			cout << "+";
	}
	cout << "+ capacity = " << v_capacity << endl;
}
#endif

template <typename T>
MyVector<T>::MyVector(int cap) // Constructor
{
	data = new T[cap]; // create a dynamic array of size cap
	v_size = 0;		   // initialize size to 0 and capacity to cap
	v_capacity = cap;
}
template <typename T> // Destructor
MyVector<T>::~MyVector()
{
	delete[] data; // delete all the data from heap
}
template <typename T>
int MyVector<T>::size() const
{
	// Return current size of vector
	return v_size;
}
template <typename T>
int MyVector<T>::capacity() const // Return capacity of vector{
{
	return v_capacity;
}
template <typename T>
bool MyVector<T>::isEmpty() const // Return true if the vector is empty, False otherwise
{
	return v_size == 0; // check for the size to determine whether the vector is empty or not
}
template <typename T>
const T &MyVector<T>::front() // Returns reference of the first element in the vector
{
	if (isEmpty()) // if vector is empty, throw exception
	{
		throw VectorEmpty();
	}
	return data[0]; // else return the front element
}
template <typename T>
const T &MyVector<T>::back() // Returns reference of the Last element in the vector
{
	if (isEmpty())
	{ // if vector is empty, throw exception
		throw VectorEmpty();
	}
	return data[v_size - 1]; // else return the last element
}
template <typename T>
void MyVector<T>::push_back(T element) // Add an element at the end of vector
{
	if (v_size == v_capacity) // if there are no more spaces(size equals capacity)
	{						  // reserve a vector of double size, reserve vector of size 1 for initial case when everything is empty
		reserve(max(1, 2 * v_capacity));
	}
	data[v_size] = element; // assign the element to the last
	v_size++;				// increase the size counter
}
template <typename T>
void MyVector<T>::insert(int index, T element) // Add an element at the index
{
	if (index > v_size - 1 || index < 0)
	{ // cannot insert an element outside of the range of vector
		throw out_of_range("Vector index out of range...!");
	}
	if (v_size == v_capacity)
	{ // if there is no extra space, reserve additional space
		reserve(max(1, 2 * v_capacity));
	}
	for (int i = v_size - 1; i >= index; i--)
	{
		data[i + 1] = data[i]; // right shift all data from the right of the index where a new value is to be inserted
	}
	data[index] = element; // insert a new element at given index
	v_size++;			   // increase the size counter
}
template <typename T>
void MyVector<T>::erase(int index) // Removes an element from the index
{
	if (index > v_size - 1 || index < 0)
	{ // cannot erase an element outside of the range of the vector
		throw out_of_range("Vector index out of range...!");
	}
	for (int i = index; i < v_size - 1; i++)
	{						   // for every element to the right of the index where data is to be erased,
		data[i] = data[i + 1]; // left shift the data
	}
	v_size--; // decrease the size
}
template <typename T>
T &MyVector<T>::operator[](int index) // Returns the reference of an element at given index
{
	if (index > v_size - 1 || index < 0)
	{ // cannot overload element at invalid index
		throw out_of_range("Vector index out of range...!");
	}
	return data[index];
}
template <typename T>
T &MyVector<T>::at(int index) // return reference of the element at given index
{
	if (index > v_size - 1 || index < 0) // there are no elements outside the range of vector
	{
		throw out_of_range("Vector index out of range...!");
	}
	return data[index]; // if the range is valid, return the value at index of the vector
}
template <typename T>
void MyVector<T>::shrink_to_fit() // Reduce vector capacity to fit its size
{
	T *temp = new T[v_size]; // create a new vector of size v_size
	v_capacity = v_size;	 // reduce the capacity to v_size
	for (int i = 0; i < v_size; i++)
	{ // copy all the elements from the previous vector to smaller new vector
		temp[i] = data[i];
	}
	delete[] data; // delete the data from previous vector
	data = temp;   // use the pointer of old array to point to the new vector
}
template <typename T>
void MyVector<T>::reserve(int cap)
{
	v_capacity = cap;				 // update the capacity of the new vector
	T *temp = new T[cap];			 // create a new array of newer capacity
	for (int i = 0; i < v_size; i++) // copy all elements of old vector to new one
	{
		temp[i] = data[i];
	}
	data = temp; // use the pointer of old array to point to the new vector
}
