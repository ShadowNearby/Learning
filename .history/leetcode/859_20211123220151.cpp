/*
 * @Date: 2021-11-23 21:34:26
 * @LastEditors: js
 * @LastEditTime: 2021-11-23 22:49:26
 * @FilePath: \code\.history\leetcode\859_20211123220151.cpp
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
        int a[26] = {0}, b[26] = {0}, ai, bi, sum = 0;
        for (int i = 0; i < sl; ++i){
            ai = int(s[i] - 'a');
            bi = int(goal[i] - 'a');
            ++a[ai];
            ++b[bi];
            if(ai != bi){
                ++sum;
            }
        }
        bool flag = false;
        if(s == goal){
            for (int i = 0; i < 26; ++i){
                if(a[i] > 1){
                    return true;
                }
            }
            return false;
        }
        for (int i = 0; i < 26; ++i){
            if(a[i] != b[i]){
                return false;
            }
            if(!flag && a[i] >= 0){
                flag = true;
            }
        }
        if(sum == 2 || (sum == 0 && flag)){
            return true;
        }
        else
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