#include "Linklist.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main(){
    string s;
    cin >> s;
    s += '\n';
    fstream a;
    a.open("main.cc", ios::out|ios::in);
    a >> s;
    int c = a.gcount();
    cout << s << endl
         << c << endl;
}