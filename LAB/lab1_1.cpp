//============================================================================
// Name         : lab1_2
// Author       : Siddhanta Paudel
// Version      : 
// Date Created : 21 May 2024
// Date Modified: 
// Description  : Take an input positive integer from the user and display
//                all the prime numbers until N
//============================================================================

#include<iostream>
using namespace std;
int check_prime(int n){
    //Function to check whether a number n is prime or not. 
    //Returns 1 if the number is prime and 0 otherwise
    
    //loop from 2 to n-1 and if there is any divisor between this range, the number is not prime
    for(int i = 2;i<n; i++){
        if(n % i == 0){
            return 0;
        }
    }
    //if there are no divisors and function doesn't return any value inside the loop, the number is prime
    return 1;
}
int main(){
   int N = -1;   //initialize the value of N before asking the value from the user.
   //take in a positive value from the user... repeat asking for value until the user inputs a positive value
   do{
        cout<<"Enter a positive number: ";
        cin >> N;
        if(N<0){
            cout<<"Invalid value. Enter a positive number"<<endl;
       }
   }while(N<0);
   //initialize counter variable prime_count and  variable check to store return values from the function
   int check = -1;
   int prime_count  = 0;
   //check for all numbers between  2 and N-1 whether they are prime or not
   for(int i = 2; i< N; i++){
        check = check_prime(i);
        if(check == 1){
            //increase the counter and display the number if it is prime
            prime_count++;
            cout<< i <<endl;
        } 
   }
   cout<< "There are "<< prime_count <<" prime numbers less than "<<N<<endl;
}