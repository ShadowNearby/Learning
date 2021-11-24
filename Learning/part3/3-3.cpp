#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int main(){
    double a,b,c,s,area;
    cout << "  " << endl;
    cin >> a >> b >> c;
    if(a+b>c&&a+c>b&&b+c>a){
    s=(a+b+c)/2;
    area=sqrt(s*(s-a)*(s-b)*(s-c));
    cout << setprecision(2) << fixed << area << endl;
    }
    else cout << " none " << endl;
    return 0;
    
}