#include<iostream>
#include<string>
using namespace std;
string str;
int main(){
    cin >> str ;
    int m=0,len = str.size();
    int n=len/2-1 ;
    for( int i = 0 ; i < str.size() ; i++){
        if (int(str[i])!=int(str[len-1])) {m++;}
        len--;
    }
    if(m==0) {cout << "yes" << endl;}
    else {cout << "no" << endl;}
    return 0;
}