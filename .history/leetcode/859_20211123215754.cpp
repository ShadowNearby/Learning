/*
 * @Date: 2021-11-23 21:34:26
 * @LastEditors: js
 * @LastEditTime: 2021-11-23 21:57:54
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
        }
        int i = 0, j = 0;
        for (i = 0; i < sl; ++i)
        {
            j = 0;
            while(j < sl){
                if(s[i] == goal[j]){
                    goal[j] = 0;
                    --gl;
                    break;
                }
                ++j;
                    if(j == gl){
                    return false;
                }
            }
            
        }
        if(gl == 0){
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