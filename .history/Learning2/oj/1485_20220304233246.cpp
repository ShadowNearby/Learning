/*
 * @Date: 2022-03-04 21:51:31
 * @LastEditors: js
 * @LastEditTime: 2022-03-04 23:32:46
 * @FilePath: \code\Learning2\oj\1485.cpp
 */
#include<iostream>
#include<vector>
#include<stack>
#include<map>
using namespace std;
int main(){
    stack<int> b;
    int n, m;
    int num;
    int ans = 0;
    cin >> n >> m;
    int *a = new int[n];
    int *c = new int[n];
    for (int i = 0; i < n; ++i){
        cin >> num;
        a[i] = num;
    }
    for (int i = 0; i < n; ++i){
        if(!b.empty()){
            while(b.top() < a[i]){
                b.pop();
                ans++;
                c[a[i]]++;
                c[b.top()]++;
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
            while(b.top() < a[i]){
                b.pop();
                ans++;
                if(b.empty()){
                    break;
                }
            }
            b.push(a[i]);
        }
        else b.push(a[i]);
    }
    
    cout << ans * 2 + n;
}