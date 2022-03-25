#include<iostream>
#include<cmath>
using namespace std;
int main(){
    int a=0,j=1;
    cin >> a;
    while(j<=a)
    {for(int i=0;i<int(11-j)/2;i++) cout << " " ;
    for(int i=0;i<j;i++) cout << "*" ;
    for(int i=0;i<int(11-j)/2;i++) cout << " " ;
    cout << endl;;
    j+=2;}
    j-=4;
    while(j>=1)
    {for(int i=0;i<(11-j)/2;i++) cout << " " ;
    for(int i=0;i<j;i++) cout << "*" ;
    for(int i=0;i<(11-j)/2;i++) cout << " " ;
    cout << endl;
    j-=2;}
    return 0;
}