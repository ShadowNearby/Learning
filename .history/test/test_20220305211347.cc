/*
 * @Date: 2021-12-24 16:38:57
 * @LastEditors: js
 * @LastEditTime: 2022-03-05 21:13:42
 * @FilePath: \code\test\test.cc
 */
#include <cstring>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
int main(){
    int *a[2];
    cout << (a + 1) - a;
}
