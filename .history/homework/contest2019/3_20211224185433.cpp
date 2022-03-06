/*
 * @Date: 2021-12-24 18:47:52
 * @LastEditors: js
 * @LastEditTime: 2021-12-24 18:54:33
 * @FilePath: \code\homework\contest2019\3.cpp
 */
#include<iostream>
#include<cstring>
using namespace std;
class Paper{
private:
    char *t;
    char **a;
    int n;
public:
    Paper(char *ti, char **au, int num, int nu){
        n = nu;
        t = ti;
        a = new char *[num];
        for (int i = 0; i < num; ++i){
            a[i] = au[i];
        }
    }
};