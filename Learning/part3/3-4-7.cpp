#include<iostream>
#include<string>
#include<iomanip>
using namespace std;
int main(){
    string str;
    cin >> str;
    int a[3];
    for(int i=0;i<4;i++){
    a[i]=(int(str[i])-49+7)%10;}
    cout << a[2]<< a[3]<< a[0]<< a[1] << endl;
    return 0;
}