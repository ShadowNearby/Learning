/*
 * @Date: 2022-03-04 21:51:31
 * @LastEditors: js
 * @LastEditTime: 2022-03-06 10:48:46
 * @FilePath: \code\Learning2\oj\1485.cpp
 */
#include<iostream>
#include<vector>
#include<stack>
using namespace std;
int main(){
    stack<int*> b;
    int n, m, j, k;
    int ans = 0;
    cin >> n >> m;
    int **a = new int*[n];
    int c[n];
    for (int i = 0; i < n; ++i){
        int *num = new int;
        cin >> *num;
        a[i] = num;
        c[i] = 0;
    }
    for (int i = 0; i < n; ++i){
        if(!b.empty()){
            while(*b.top() < *a[i]){
                ans++;
                c[i]++;
                c[(b.top() - a[0]) / 16]++;
                b.pop();
                if(b.empty()){
                    break;
                }
            }
            b.push(a[i]);
        }
        else b.push(a[i]);
    }
    while(!b.empty()){
        b.pop();
    }
    for (int i = n - 1; i >= 0; --i){
        if(!b.empty()){
            while(*b.top() < *a[i]){
                ans++;
                c[i]++;
                c[(b.top() - a[0])  / 16]++;
                b.pop();
                if(b.empty()){
                    break;
                }
            }
            b.push(a[i]);
        }
        else b.push(a[i]);
    }

    cout << ans * 2 + n << endl;
    int d[n];
    
}