#include<iostream>
using namespace std;
int main( ){
    int m=0;
    char ch,v[5]={'a','e','i','o','u'};
    cin >> ch;
    for(int i=0;i<5;i++){
        if(ch==v[i]) m=1;}
        if(m==0&&ch>='a'&&ch<='z') m=2;
        switch(m){
        case 1:{cout << "vowel" << endl;}break;
        case 2:{cout << "non-vowel" << endl;}break;
        default :{cout << "non-character" << endl;}break;
        }
    return 0;
}