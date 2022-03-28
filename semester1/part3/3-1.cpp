#include<iostream>
using namespace std;
int main(){
    int fee=0;
    cin >> fee ;
     if(fee<2000&&fee>=1000){
        cout << fee*0.9 << endl;
    }if(fee<3000&&fee>=2000){
        cout << fee*0.8 << endl;
    }if(fee<4000&&fee>=3000){
        cout << fee*0.7 << endl;
    }if(fee<5000&&fee>=4000){
        cout << fee*0.6 << endl;
    }if(fee>=5000){
        cout << fee*0.5 << endl;
    }
    return 0;
}
