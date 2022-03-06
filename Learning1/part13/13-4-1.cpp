#include<iostream>
using namespace std;
class Time{
    private:
        int hour;
        int minute;
        int second;
    public:
    Time(int h,int m,int s){
        
        hour = h;
        minute = m;
        second = s;
    }
    ~Time(){
    }
    void gettime(int h,int m,int s){
        hour = h;
        minute = m;
        second = s;
    }
    void print(){
        if(hour<10){
            cout << "0";
        }
        cout << hour <<":";
        if(minute<10){
            cout << "0";
        }
        cout << minute <<":";
        if(second<10){
            cout << "0";
        }
        cout << second << endl;
    }
};
int main(){
    return 0;
}