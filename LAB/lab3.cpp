/**
 * @file lab5.cpp
 * @author Siddhanta Paudel
 * @description This program convert an Infix expression to PostFix and then evaluate it
 * @date	28May 2024
 */
// starter_code_begins
#include <iostream>
#include <string>
#include <exception>
#include <math.h>
#include <ctype.h>

using namespace std;

//=============MyStack Class ================
template <typename T>
class MyStack
{
private:
	T *array;
	int n; // number of current elements in the MyStack
	int N; // Array Size (Capacity)
public:
	MyStack(int N = 50); // we set default capacity of stack as 50
	~MyStack();
	void push(T); // Push an elemet in the stack
	void pop();	  // pop/remove the element at the tos
	T &top();	  // return reference of the top element
	int size();	  // return current size of MyStack
	bool empty(); // returns true if the stack is Empty
};
//=============================================
bool isOperator(char);				// Function that checks if the input char is an operator
bool isgeq(char, char);				// Helper function that compare two operators  and return True if the presedence of first operator is greater than or equal to the second operator
int convertOpToInt(char);			// Function that converts operators into int so their precdence can be compared
string infix2postfix(string);		// Function that converts an infix notaiton into a postfix notation (lab4)
float evaluate(string postfix);		// Function that will evaluate a PostfixExpression and return the result
bool isBalanced(string expression); // Funciton that will check for balanced parentheses
bool isOperand(char a);				// function that will check whether the characte is a digit from 0 to 9 or no
//==========================================
int main()
{

	while (true)
	{
		string infix; // Infix expression
		cout << "Enter an Infix Expression: ";
		cin >> infix;
		try
		{
			if (infix == "exit")
				break;

			else if (!isBalanced(infix))
			{
				cout << "Expression is not Balanced " << endl;
				continue;
			}

			string postfix = infix2postfix(infix); // Postfix Expression
			cout << "The postfix form is: " << postfix << endl;
			float ans = evaluate(postfix);		 // evaluate the postfix Expresion
			cout << infix << "=" << ans << endl; // print the final answer
		}
		catch (exception &e)
		{
			cout << "Exception: " << e.what() << endl;
		}
	}

	return EXIT_SUCCESS;
}
//==========================================
// Function that checks if a given char is a valid operator or not.
bool isOperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
		return true;
	else
		return false;
}
//==========================================
// Function that converts operators into an integer so its precdence can be checked
int convertOpToInt(char ch)
{
	if (ch == '+' || ch == '-')
		return 1;
	if (ch == '*' || ch == '/')
		return 2;
	if (ch == '^')
		return 3;
	return 0;
}
// Helper method that compare two operators and return true if first operator
// has greater or equal predence than the second operator
bool isgeq(char opA, char opB)
{
	return (convertOpToInt(opA) >= convertOpToInt(opB));
}
// starter_code_ends
//===============================================================================
//  == Define the methods of My Stack and other functions below this line.
//===============================================================================
template <typename T>
MyStack<T>::MyStack(int N)
{
	this->N = N;
	array = new T[N]; // dynamically create an array of size N so that the array doesn't get destroyed once constructor call is done
	n = -1;			  // initially the total no of elements = 0;
}
// push method
template <typename T>
void MyStack<T>::push(T x)
{
	if (n == N)
	{
		throw logic_error("Stack is Full");
	}
	*(array + ++n) = x; // add element to the nth element of the array, initially n is 0, and n is the number of elements
						// increase the number of elements;
}
// pop method
template <typename T>
void MyStack<T>::pop()
{
	if (empty())
	{ // if there are no elements in the stack, it can't be popped
		throw logic_error("Stack is empty.");
	}
	--n; // let the element be as it is....reduce the number of elements
}
template <typename T>
bool MyStack<T>::empty()
{
	return n < 0; // check if the number of elements is 0 or not
}
template <typename T>
int MyStack<T>::size()
{
	return n + 1;
}
template <typename T>
T &MyStack<T>::top()
{
	if (empty())
	{ // if there are no elements in the stack, it doesn't have a top element
		throw runtime_error("Stack is empty.");
	}
	else
	{
		return array[n];
	}
}
template <typename T>
MyStack<T>::~MyStack()
{
	delete[] array;
}
// additional functions outside the class
// check whetther the given expression is balanced or not
bool isBalanced(string expression)
{
	MyStack<char> parenthesis;
	int length = expression.length();
	for (int i = 0; i < length; i++)
	{//if the expression is (, push it onto the stack
		if (expression[i] == '(')
		{
			parenthesis.push('(');
		}
		else if (expression[i] == ')')
		{//if ) is found, return false if the stack is empty else pop the element from the stack
			if (parenthesis.empty())
			{
				return false;
			}
			parenthesis.pop();
		}
	}
	//if the stack is empty, the expression is balanced else it is not balanced
	return parenthesis.empty();
}
//return whether the character is an operand or not
bool isOperand(char a)
{
	return ((a - '0') < 10 && (a - '0') >= 0);
}
string infix2postfix(string INFIX)
{
	int length = INFIX.length();
	char temp;
	//create a dynamic character array of size length+1, 1 extra space for null character
	char *POSTFIX = new char[length + 1];
	char top_stack;
	int postfix_count = 0;
	//create a character stack of length "length"
	MyStack<char> instack(length);
	for (int i = 0; i < length; i++)
	{
		temp = INFIX[i];
		if (isOperand(temp))
		{//if the character is an operand, add to the POSTFIX
			POSTFIX[postfix_count] = temp;
			postfix_count++;
		}
		else if (temp == '(')
		{//if the character is (, push to the stack
			instack.push(temp);
		}
		else if (isOperator(temp))
		{
			if (instack.empty())
			{ // if there is nothing else in the stack, push the operator into the stack
				// cout<<temp<<"is pushed to the stack"<<endl;
				instack.push(temp);
			}
			else
			{ // if the stack is not empty
				// add to postfix all operators with same or higher precedence until ( , lower or empty stack
				while (!instack.empty() && instack.top() != '(' && isgeq(instack.top(), temp))
				{	top_stack = instack.top();
					POSTFIX[postfix_count] = top_stack;
					postfix_count++;
					instack.pop();
				}
				//after all valid operators on the stack have been transferred to POSTFIX, push temp onto the stack
				instack.push(temp);
			}
		}
		else if (temp == ')')
		{
			// cout<<") is found here. last part of the code"<<endl;
			while (!instack.empty() && instack.top() != '(' )
			{
				top_stack = instack.top();
				//cout << "last part of the code..... top of the stack is " << top_stack << endl;
				POSTFIX[postfix_count] = top_stack;
				postfix_count++;
				instack.pop();
			}
			if(!instack.empty() && instack.top() =='(')
			{//if the top element is ( , just pop
				instack.pop();
			}
		}
	}
	// after the loop finishes and the scanning is complete
	while (!instack.empty())
	{//add to postfix the remaining operators in the stack
		top_stack = instack.top();
		POSTFIX[postfix_count] = top_stack;
		postfix_count++;
		instack.pop();
	}
	//add null character at the end of the character array
	POSTFIX[length] = '\0';
	string final(POSTFIX);
	//free up the memory for the dynamically created POSTFIX character array
	delete []POSTFIX;
	return final;
}
// Function that will evaluate a PostfixExpression and return the result
float evaluate(string postfix)
{
	int length = postfix.length();
	char temp;		//to take in the characters from postfix
	float expression(0);
	float f1;
	float f2;
	MyStack<float> Stack(length);
	for (int i = 0; i < length; i++)
	{
		temp = postfix[i];
		if (isOperand(temp))
		{	//if the ith element of postfix string is operator, convert it to a float and push it onto the stack
			Stack.push((float)(temp - '0'));
		}
		if (isOperator(temp))
		{	//take the digits from top, store them in variables and pop them
			f1 = Stack.top();
			Stack.pop();
			f2 = Stack.top();
			Stack.pop();
			//f2 is the first digit and f1 is the second digit
			//switch cases for different operators
			switch (temp)
			{
			case '+':
				expression = f2 + f1;
				break;
			case '-':
				expression = f2 - f1;
				break;
			case '*':
				expression = f2 * f1;
				break;
			case '/':
				if (f1 != 0)
				{
					expression = f2 / f1;
				}
				else
				{
					throw logic_error("Division by 0");
				}
				break;
			case '^': 
				expression = pow(f2, f1);
				break;
			default:
				continue;
			}
			//push the final evaluated expression into the stack after every evaluation
			Stack.push(expression);
		}
	}
	//the only remaining value in the stack is the evaluated answer
	return Stack.top();
}
