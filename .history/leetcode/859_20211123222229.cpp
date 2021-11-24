/*
 * @Date: 2021-11-23 21:34:26
 * @LastEditors: js
 * @LastEditTime: 2021-11-23 22:22:29
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
        int i = sl - 1, j = 0, ti = sl;
        while(i >= 0){
            if(s[i] != goal[i]){
                if(j == 0){
                    ti = i;
                }
                ++j;
            }
            if(j == 2){
                break;
            }
            --i;
        }
        if(j == 2 && s[i] != s[ti]){
            return true;
        }
        return false;
    }
};
int main(){
    string a, b;
    Solution s;
    cin >> a >> b;
    cout << s.buddyStrings(a, b);
    return 0;
}