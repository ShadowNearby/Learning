#include<iostream>
#include<cmath>
#include<string>
using namespace std;
int main(){
    int odd=0,even=0;
    string str;
    cin >> str;
    cout << str <<endl;
    for(int i=0;i<str.size();i++){
        if(int(str[i]%2==0)) even++;
        if(int(str[i]%2!=0)) odd++;
    }
    int a=even,b=odd,c=str.size();
    cout << a << b << c << endl;
    while(a!=1||b!=2){
        int tempa=0,tempb=0;
        if (a%2==0){tempa++;}
        if (b%2==0){tempa++;}
        if (c%2==0){tempa++;}
        if (a%2!=0){tempb++;}
        if (b%2!=0){tempb++;}
        if (c%2!=0){tempb++;}
        c=3;
        a=tempa;
        b=tempb;
        cout << a << b << c << endl;
    }
    return 0;
}