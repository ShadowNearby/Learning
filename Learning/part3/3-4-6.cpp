#include<iostream>
#include<string>
#include<iomanip>
using namespace std;
int main(){
    double a,d;
    int b;
    char c;
    cin >> a >> b >> c ;
    switch(b){
        case 90: d=5.82*double(a);break;
        case 93: d=5.96*double(a);break;
        case 97: d=6.36*double(a);break;
        default: d=5.59*double(a);break;
    }
    switch(c){
        case 's':d=d*0.95;break;
        default :d=d*0.98;break;
    }
    cout << setprecision(2)<< fixed<< d << endl;
    return 0;

}