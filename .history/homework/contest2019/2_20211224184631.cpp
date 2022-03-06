/*
 * @Date: 2021-12-24 18:41:15
 * @LastEditors: js
 * @LastEditTime: 2021-12-24 18:46:05
 * @FilePath: \code\homework\contest2019\2.cpp
 */
#include<iostream>
using namespace std;
void print(int n){
    if(n == 0){
        return;
    }
    else{
        for (int i = 0; i < 4 - n; ++i){
            cout << " ";
        }
        for (int i = 0; i < 2 * n - 1; ++i){
            cout << "*";
        }
        for (int i = 0; i < 4 - n; ++i){
            cout << " ";
        }
        print(n - 1);
    }
    return;
}
int main(){
    print(4);
    return 0;
}