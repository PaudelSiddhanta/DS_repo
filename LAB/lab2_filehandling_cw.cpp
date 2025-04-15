#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std;
int main()
{
    // int a = 5;
    // char ch = 'z';
    // float f = 4.5f
    ofstream fout("file1.txt");
    // // fout.open("file1.txt", ios::app);
    // if (fout.is_open())
    // {
    //     cout << "file successfully opened" << endl;
    //     fout << "tero baaje sala"<<endl;
    //     fout<<"data structures"<<endl;
    // }
    // else
    // {
    //     perror("");
    //     return -1;
    // }

    // fout.close();
    char ch;
    ifstream fin("file1.txt");
    if(fin)    //if(fin.is_open())
    {
        fin>>ch;
        cout<<ch<<endl;
        fin.close();
    }
    else{   
        perror("");
    }
    return 0;
}