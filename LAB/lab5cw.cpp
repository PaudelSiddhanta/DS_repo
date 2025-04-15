#include<iostream>
using namespace std;
int add(int a=-1, int b=5);
int main(){
    int a;
    int b;
    cout<<"the sum is "<<add()<<endl;
    cout<<"the sum is "<<add(5,6)<<endl;
}
int add(int a, int b){
    return a+b;
}