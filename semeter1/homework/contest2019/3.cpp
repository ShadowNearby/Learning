/*
 * @Date: 2021-12-24 18:47:52
 * @LastEditors: js
 * @LastEditTime: 2021-12-24 19:02:49
 * @FilePath: \code\homework\contest2019\3.cpp
 */
#include<iostream>
#include<cstring>
using namespace std;
int f(int n){
    int temp;
    switch(n){
        case 0:
        case 1:
            return 1;
        default:
            temp = (n - 1) * f(n - 2);
            cout << temp << " ";
            return temp;
    }
}
int main(){
    cout << f(6);
    return 0;
}