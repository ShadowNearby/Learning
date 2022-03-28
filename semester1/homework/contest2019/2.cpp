/*
 * @Date: 2021-12-24 18:41:15
 * @LastEditors: js
 * @LastEditTime: 2021-12-24 18:47:21
 * @FilePath: \code\homework\contest2019\2.cpp
 */
#include<iostream>
using namespace std;
void print(int n){
    if(n == 0){
        return;
    }
    else{
        for (int i = 0; i < n; ++i){
            cout << " ";
        }
        for (int i = 0; i < 9 - 2 * n; ++i){
            cout << "*";
        }
        for (int i = 0; i < n; ++i){
            cout << " ";
        }
        cout << endl;
        print(n - 1);
    }
    return;
}
int main(){
    print(4);
    return 0;
}