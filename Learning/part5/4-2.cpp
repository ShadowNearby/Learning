#include<iostream>
using namespace std;
int main(){
    int i=-1;
    int a[3]={0},b[3]={0};
    for(i=0;i<6;i++) b[i]=i;
    cout << endl;
    for(i=0;i<3;i++) cout << a[i] << ' ';
    cout << endl;
    i=8;
    a[3]=-100;
    cout << i;
    return 0;
}