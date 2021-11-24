/*
 * @Date: 2021-11-24 20:23:02
 * @LastEditors: js
 * @LastEditTime: 2021-11-24 21:21:02
 * @FilePath: \code\leetcode\423.cpp
 */
#include <string>
#include <iostream>
using namespace std;
class Solution {
public:
    string originalDigits(string s) {
        int ch[22] = {0}, len = s.size(), n, count[10] = {0};
        string ans;
        for (int i = 0; i < len; ++i){
            n = int(s[i]) - 101;
            ++ch[n];
        }
        count[0] = ch[21];
        count[2] = ch[18];
        count[4] = ch[16];
        count[6] = ch[19];
        count[8] = ch[2];
        count[]
        return ans;
    }
};
int main(){
    Solution s;
    cout << s.originalDigits("zeroonetwothreefourfivesixseveneightnine");
    return 0;
}
//s[i] 为 ["e","g","f","i","h","o","n","s","r","u","t","w","v","x","z"]
//         101 103 102 105 104 111 110 115 114 117 116 119 118 120 122
//          0   2   1   4   3   10  9  14  13  16  15  18  17  19  21