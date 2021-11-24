#include<iostream>
#include<cmath>
 //in out stream
 #include<iomanip>
using namespace std;
int main(){
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    double sum=(double(a)+b+c+d)/4 ;
    cout <<   setprecision(1) << fixed << sum << endl;

    return 0;
}