#include<iostream>
#include<cmath>
using namespace std;
int main(){
    int a=0,n=0,sum=0,b=0;
    cin >> a >>n;
    for(int i=0;i<n;i++){
        sum = sum  + a*pow(10,double(i));
        b = b+sum;
    }
    cout << b << endl;
    return 0;
}