/*
 * @Date: 2021-11-23 21:34:26
 * @LastEditors: js
 * @LastEditTime: 2021-11-23 21:47:14
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
        int i = 0, j = 0;
        for (i = 0; i < sl; ++i)
        {
            j = 0;
            while(j < sl){
                if(s[i] == goal[j]){
                    goal[j] = 0;
                    break;
                }
                ++j;
            }
            if(j == sl){
                return false;
            }
        }
        if(goal == ""){
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