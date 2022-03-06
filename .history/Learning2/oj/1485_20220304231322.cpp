/*
 * @Date: 2022-03-04 21:51:31
 * @LastEditors: js
 * @LastEditTime: 2022-03-04 23:13:22
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
    cin >> n >> m;
    for (int i = 0; i < n; ++i){
        cin >> num;
        a.push_back(num);
    }
    for (int i = 0; i < n; ++i){
        while(b.top < a[i]){
            b.pop();
            ans++;
            if(b.empty()){
                break;
            }
        }
    }
    b = 0;
    for (int i = n - 1; i >= 0; --i){
        while(b.top < a[i]){
            b.pop();
            ans++;
            if(b.empty()){
                break;
            }
        }
    }
    cout << ans;
}