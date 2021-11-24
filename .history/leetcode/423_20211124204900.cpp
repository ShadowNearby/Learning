/*
 * @Date: 2021-11-24 20:23:02
 * @LastEditors: js
 * @LastEditTime: 2021-11-24 20:49:00
 * @FilePath: \code\leetcode\423.cpp
 */
class Solution {
public:
    string originalDigits(string s) {
        int ch[21] = {0}, len = s.size(), s;
        string ans;
        for (int i = 0; i < len; ++i){
            s = int(s[i]) - 101;
            ++ch[s];
        }
        while(ch[21] > 0 && ch[0] > 0 && ch[13] > 0 && ch[10] > 0){
            ans += '0';
            --ch[21];
            --ch[0];
            --ch[13];
            --ch[10];
        }
        while(ch[0] > 0 && ch[9] > 0 && ch[10] > 0){
            ans += '1';
            --ch[0];
            --ch[9];
            --ch[10];
        }
        while(ch[15] > 0 && ch[18] > 0 && ch[10] > 0){
            ans += '2';
            --ch[15];
            --ch[18];
            --ch[10];
        }
        while(ch[15] > 0 && ch[0] > 1 && ch[3] > 0 && ch[16] > 0){
            ans += '3';
            --ch[15];
            --ch[0];
            --ch[0];
            --ch[3];
            --ch[16];
        }
        while(ch[1] > 0 && ch[10] > 0 && ch[16] > 0 && ch[13] > 0){
            ans += '4';
            --ch[1];
            --ch[10];
            --ch[16];
            --ch[13];
        }
        while(ch[1] > 0 && ch[4] > 0 && ch[17] > 0 && ch[0] > 0){
            ans += '5';
            --ch[1];
            --ch[4];
            --ch[17];
            --ch[0];
        }
        while(ch[14] > 0 && ch[4] > 0 && ch[19] > 0){
            ans += '6';
            --ch[14];
            --ch[4];
            --ch[19];
        }
        while(ch[14] > 0 && ch[0] > 1 && ch[17] > 0 && ch[9] > 0){
            ans += '7';
            --ch[14];
            --ch[0];
            --ch[0];
            --ch[17];
            --ch[9];
        }
        while(ch[0] > 0 && ch[4] > 0 && ch[2] > 0 && ch[3] > 0 && ch[15] > 0){
            ans += '8';
            --ch[0];
            --ch[4];
            --ch[2];
            --ch[3];
            --ch[15];
        }
        while(ch[9] > 1 && ch[4] > 0  && ch[0] > 0){
            ans += '9';
            --ch[9];
            --ch[0];
            --ch[17];
            --ch[9];
        }
        return ans;
    }
};
//s[i] 为 ["e","g","f","i","h","o","n","s","r","u","t","w","v","x","z"]
//         101 103 102 105 104 111 110 115 114 117 116 119 118 120 122
//          0   2   1   4   3   10  9  14  13  16  15  18  17  19  21