#include<iostream>
using namespace std;
int main(){
    double a=0,b=0;
    cin >> a;
    if(a<=10){
        b=1.5*a;
    }
    else{
        b=1.5*10+(a-10)*2;
    }
    cout << b << endl;
    return 0;
}