#include<iostream>
#include<exception>
using namespace std;

class MyException: public exception
{
	public:
		virtual const char* what() const throw()
		{
			return "My Exception..!";
		}

};

int main()
{

	try
	{
		throw MyException();
		throw "blah blah";
		throw logic_error("some run time error.");

	}
	catch(runtime_error& rex)
	{
		cout<<rex.what()<<endl;
	}
	catch (exception &ex)
	{
		cout<<ex.what()<<endl;
	}
	
	cout<<"Graceful termination of the program.!"<<endl;
}