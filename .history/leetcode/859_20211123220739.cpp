/*
 * @Date: 2021-11-23 21:34:26
 * @LastEditors: js
 * @LastEditTime: 2021-11-23 22:07:39
 * @FilePath: \code\leetcode\859.cpp
 */
#include <iostream>
#include <string>
using namespace std;
class Solution {
public:
    bool buddyStrings(string s, string goal) {
        int sl = s.size(), gl = goal.size();
        if(sl != gl){
            return false;
        }
        if(s == goal){
            int a = 0, b = 0;
            while(a < sl){
                while(b < sl - 1){
                    b = a + 1;
                    if(s[a] == s[b]){
                        return true;
                    }
                    ++b;
                }
                ++a;
            }
            return false;
        }
        int i, j, num = 0;
    }
};
int main(){
    string a, b;
    Solution s;
    cin >> a >> b;
    cout << s.buddyStrings(a, b);
    return 0;
}