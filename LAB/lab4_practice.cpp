#include <iostream>
using namespace std;
class Time
{
private:
    int hours;
    int minutes;

public:
    Time (int hours = 0, int minutes = 0): hours(hours), minutes(minutes){}
    void setTime(int, int);
    void getTime();
    const Time& operator++(){       //prefix increment
        if(minutes>0 & minutes <59){
            this->minutes++;
        }
        else{
            this->hours++;
            this->minutes=0;
        }
        return *this;
    }
    Time operator++(int){       //postfix increment
        Time tmp(*this);
        if(minutes>0 & minutes <59){
            this->minutes++;
        }
        else{
            this->hours++;
            this->minutes=0;
        }
        return tmp;
    }
};
//===============================================
int main(){
   // Time T1;
    Time T2(3,4);
    T2.getTime();
    Time T3 = ++T2; //prefix
    Time T4 = T2++; //postfix
   // T1.setTime(12,30);
    //T1.getTime();
    T2.getTime();
    T3.getTime();
}







//================================================//
void Time :: setTime(int h, int m){
    this->hours = h;
    this->minutes = m;
}
void Time :: getTime(){
    cout<<this->hours<<" : "<<this->minutes<<endl;

}