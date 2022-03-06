/*
 * @Date: 2022-03-04 21:51:31
 * @LastEditors: js
 * @LastEditTime: 2022-03-04 23:18:55
 * @FilePath: \code\Learning2\oj\1485.cpp
 */
#include<iostream>
#include<vector>
#include<stack>
using namespace std;
int main(){
    vector<int> a;
    stack<int> b,c;
    int n, m;
    int num;
    int ans = 0;
    cin >> n;
    for (int i = 0; i < n; ++i){
        cin >> num;
        a.push_back(num);
    }
    for (int i = 0; i < n; ++i){
        if(!b.empty())
        while(b.top() < a[i]){
            b.pop();
            ans++;
            if(b.empty()){
                break;
            }
        }
        if(b.empty()) b.push(a[i]);
    }
    while(!b.empty()){
        b.pop();
    }
    for (int i = n - 1; i >= 0; --i){
        if(!b.empty())
        while(b.top() < a[i]){
            b.pop();
            ans++;
            if(b.empty()){
                break;
            }
        }
        if(b.empty()) b.push(a[i]);
    }
    cout << ans * 2 + n;
}