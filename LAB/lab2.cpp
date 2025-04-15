//============================================================================
// Name         : lab2.cpp
// Author       :   Siddhanta Paudel
// Version      : 1.0
// Date Created :  24 May 2024
// Date Modified:
// Description  : Singly Linked-List implementation in C++
//============================================================================
// starter_code_begins
#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <sstream>
using namespace std;
//====================================
class Node
{
private:
	int elem;	// data element
	Node *next; // Link (pointer) to the next Node

public:
	Node(int elem) : elem(elem), next(NULL)
	{
	}
	friend class MyLinkedList;
};
//=====================================
class MyLinkedList
{
private:
	Node *head; // pointer to the head of list
public:
	MyLinkedList();							// empty list constructor
	~MyLinkedList();						// destructor to clean up all nodes
	bool empty() const;						// is list empty?
	void addFront(int elem);				// add a new Node at the front of the list
	void removeFront();						// remove front Node from the list
	void remove(int elem);					// remove the first occurrence of an element of the list, if the element exists.
	unsigned int countElem(int elem) const; // count frequency of an element in the list
	int getIndexOf(int elem) const;			// returns first index of an element in the list, -1 if the element is not present
	void display() const;
	void readData(string);		  // read a file and load it into the linked list
	void writeData(string) const; // write the linked list to a file
};
//=====================================
void listCommands()
{
	cout << "List of available Commands:" << endl
		 << "display            : Display the Linked List" << endl
		 << "addFront <element> : Add <element> to the front of the Linked List" << endl
		 << "removeFront        : Remove the front node of the Linked List" << endl
		 << "remove        	    : Remove the first occurrence of an element of the list (if exists)" << endl
		 << "count <element>    : count frequency of an element in the list" << endl
		 << "indexOf <element>  : return first index of an element in the list (-1 of not present)" << endl
		 << "read <file_name>   : Load the data from <file> and add it into the Linked List" << endl
		 << "write <file_name>  : Dump the contents of the Linked list to <file>" << endl
		 << "help               : Display the list of available commands" << endl
		 << "exit               : Exit the Program" << endl;
}
//=======================================
// main function
int main()
{
	MyLinkedList myList;

	listCommands();
	string user_input;
	string command;
	string parameter;

	do
	{
		cout << ">";
		getline(cin, user_input);

		// parse user input into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr, command, ' ');
		getline(sstr, parameter);

		if(command=="display") 				myList.display();
		 else if(command=="addFront" or command=="af")				myList.addFront(stoi(parameter)),myList.display();
		 else if(command=="removeFront" or command=="rf")			myList.removeFront(),myList.display();
		 else if(command=="remove" or command=="r")         			myList.remove(stoi(parameter)),myList.display();
		 else if(command=="count")			cout<<parameter<<" occurs "<<myList.countElem(stoi(parameter))<<" time(s) in the list"<<endl;
		 else if(command=="indexOf")         cout<<"First index of "<<parameter<<" in the list is: "<<myList.getIndexOf(stoi(parameter))<<endl;
		 else if(command=="read")			myList.readData(parameter),myList.display();
		 else if(command == "write")			myList.writeData(parameter);
		 else if(command == "help")			listCommands();
		 else if(command == "exit")			break;
		else 								cout<<"Invalid Commad !!"<<endl;
	} while (command != "exit");

	return EXIT_SUCCESS;
}
//====================================
// constructor
MyLinkedList::MyLinkedList()
{
	//point head to null
	this->head = NULL;
}
// starter_code_ends
//====================================
//  destructor to clean up all nodes
MyLinkedList::~MyLinkedList()
{
	// to-do
	//keep on removing the front node until everything is removed
	while (!empty())
	{
		removeFront();
	}
}
//====================================
// Check if the list is empty or not
bool MyLinkedList::empty() const
{	
	//return whether head still points to null or not to check whether the list is empty or not
	return head == NULL;
}
// to-do
//====================================
// add a node at the front of list
void MyLinkedList::addFront(int elem)
{
	// to-do
	//add a new node
	Node *v = new Node(elem);
	//make the head point to the added node and new node point to the next node after that
	v->next = head;
	head = v;
	// v->elem = elem;
}
//====================================
// remove the first node from the list
void MyLinkedList::removeFront()
{
	// to-do
	if (empty())
	{
		cout << "The list is empty." << endl;
	}
	else
	{
		//add a  pointer to head and make the header point to the next node
		Node *temp = head;
		head = temp->next;
		//delete the header
		delete temp;
	}
}
//=====================================
// remove the first occurrence of an element of the list, if the element exists
void MyLinkedList::remove(int elem)
{
	// to-do
	Node *ptr = head;
	if (ptr->elem == elem)
	{ // if the element is present in the very first node, remove the first element
		removeFront();
	}
	else
	{
		while (ptr->next->elem != elem)
		{ // until we find the node previous to our required node, we update the pointer
			ptr = ptr->next;
		}
		if (ptr->next->elem == elem)
		{ // when we find the node1(node before requrired node),
		  //  we change the next pointer of the node1 to next of required node and delete required node
			Node *temp = ptr->next;
			ptr->next = temp->next;
			delete temp;
		}
		cout<<"First occurence of "<<elem<<" has been succcessfully deleted from the list."<<endl;
	}
}
//====================================
// count frequency of an element in the list
unsigned int MyLinkedList::countElem(int elem) const
{
	// initialize a counter to 0
	int count = 0;
	Node *ptr = head;
	//check until the last element
	while (ptr != NULL)
	{
		if (ptr->elem == elem)
		{	//if element is present, increase the counter
			count++;
		}
		ptr = ptr->next;		//go to the next node
	}
	return count;		//return the number of elements counted
}
//==============================================
// get first index of an element in the the list.
// returns -1 if the element is not present
int MyLinkedList::getIndexOf(int elem) const
{
	// initialize a pointer to head and an index to 0
	Node *ptr = head;
	int index = 0;
	//loop until the last element
	while (ptr != NULL)
	{
		if (ptr->elem == elem)
		{	//if the element is found, return the index
			return index;
		}
		index++;		//if the element is not found, increase the index and go to the next node
		ptr = ptr->next;
	}
	return -1;		//if the element is not found, return -1 
}
//==============================================
// display all nodes of the linked list
void MyLinkedList::display() const
{
	// initialize a pointer and point it to the initial node
	cout << "Head->";
	Node *ptr;
	ptr = head;
	//loop until the last node in the pointer
	while (ptr != NULL)
	{	//display the element in the current node
		cout << ptr->elem << "->";
		//go to the next node after displaying the element 
		ptr = ptr->next;
	}
	cout << "NULL" << endl;
}
//==============================================
// Load data from a file and add it to the Linked List
void MyLinkedList::readData(string path)
{
	//declare a variable to take the input
	int n;
	ifstream fin(path);		//open the file
	while(!fin.eof()){		//loop values until the end of file
		fin>>n;			//take in the value
		addFront(n);		//add the value to the start of the node
	}
	removeFront();			//remove the front value to remove repitition of the last element
	fin.close();			//close the file
}
//=============================================
// Dump/write the contents of the list to a file
void MyLinkedList::writeData(string path) const
{
	// to-do
	if (empty())
	{
		cout << "The List is empty" << endl;
	}
	else
	{		//if the list is not empty, open a new file
		ofstream fout(path);
		if (fout)		//if file opening doesn't fail
		{
			int count = 0;
			Node *temp = head;		//declare a pointer to point to the initial node
			while (temp != NULL)		//repeat until the last node
			{
				fout << temp->elem << endl;			//write the element of the current node in the file
				temp = temp->next;			//point to the next pointer
				count++;
			}
			cout << count << " records have been exported to " << path << endl;
			fout.close();			//close the file
		}
	}
}
//==================================================
