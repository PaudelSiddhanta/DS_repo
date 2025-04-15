#include<iostream>
#include<fstream>
#include<stdio.h>
#include<iomanip>
using namespace std;
class Student{
    private:
        string name;
        int id;
    public:
        Student(string n="", int i=0){
            name = n;
            id = i;
        }
        void print(){
            
            cout << left << setw(10) << "Name: " << setw(10) << name; // Adjust setw according to maximum name length
            cout << right << setw(10) << "ID: " << setw(10) << id << endl; // Adjust setw according to maximum number of digits in ID
        }
        
};
int main(){
    ifstream fin("students.dat");
    if(fin){
        fin.seekg(0,ios::end);
        cout<<fin.tellg();
        int size = fin.tellg()/sizeof(Student);  
        cout<<size;
        Student *cs_students = new Student[size];
        fin.seekg(0, ios::beg);
        fin.read(reinterpret_cast<char*>(&cs_students),size*sizeof(Student));
        for(int i = 0; i<size; i++){
            cs_students[i].print();
        }
        fin.close();
        delete[] cs_students;

    }
}