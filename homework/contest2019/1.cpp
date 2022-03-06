/*
 * @Date: 2021-12-24 18:36:24
 * @LastEditors: js
 * @LastEditTime: 2021-12-24 18:40:10
 * @FilePath: \code\homework\contest2019\1.cpp
 */
#include<iostream>
using namespace std;
int main(){
    int num;
    for (int i = 1; i < 1000; ++i){
        num = 0;
        for (int j = 1; j < i; ++j){
            if(i % j == 0){
                num += j;
            }
        }
        if(num == i){
            cout << i << " ";
        }
    }
    return 0;
}