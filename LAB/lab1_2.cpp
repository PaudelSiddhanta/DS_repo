//============================================================================
// Name         : lab1_2
// Author       : Siddhanta Paudel
// Version      : 
// Date Created : 21 May 2024
// Date Modified: 
// Description  : Find the minimum and the maximum values in an Array using a 
//				  function (findMinMax) that takes the array, its size and
//				  two variables min and max by reference. 
//============================================================================
#include<iostream>
#include<cstdlib>
using namespace std;

void findMinMax(int[],int, int&, int&);	//function declaration

int main(void)
{
	//Declare variables and assign negative values just to initialize them
	int size(-1), min(-1), max(-1);

	//Prompt user to enter the size of the dynamic array
	do{
		cout<<"Enter the size of the array: ";
		cin >> size;
		if(size < 0){
			cout<<"Invalid value. Enter a positive number"<<endl;
		}
	}while(size <0);

	//Create a dynamic array
	int *arrPtr = new int[size];

	//Populate the array with random values
	srand(time(NULL));
	for(int i = 0 ; i< size ;  i++){
		*(arrPtr + i) = rand()%101;
	}

	//Call the function finMinMax()
	findMinMax(arrPtr,size,min,max);

	//Print the values of array followed by min and max values
	for(int i = 0 ; i< size ;  i++){		
		cout<< "array["<<i<<"] = "<<*(arrPtr+i)<<endl;
	}
	cout<< "Min : "<< min<<endl;
	cout<< "Max : "<< max<<endl;

	//Do Necessary cleanup, e.g. delete dynamically allocated memory.
	delete[] arrPtr;
	return EXIT_SUCCESS;
}

//Function Definition
void findMinMax(int array[], int arraySize, int& min, int& max)
{
	//assign both min and max to the first element of the array
	min  = array[0];
	max = array[0];
	for(int i = 1; i < arraySize; i++){
		
		//if any element is less than min, update min value
		if(array[i] < min){
			min = array[i];
		}

		//if any element is greater than max, update max value
		if(array[i]> max){
			max = array[i];
		}
	}
	
}
