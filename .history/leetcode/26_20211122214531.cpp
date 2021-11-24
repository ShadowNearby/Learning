/*
 * @Date: 2021-11-22 21:25:24
 * @LastEditors: js
 * @LastEditTime: 2021-11-22 21:45:31
 * @FilePath: \code\leetcode\26.cpp
 */
#include <vector>
using namespace std;
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int len = nums.size();
        if(len == 0){
            return 0;
        }
        int i = 0, j;
        while(i < len){
            j = i;
            while(j < len){
                ++j;
                if(nums[i] == nums[j]){
                    ++i;
                    --len;
                    break;
                }
            }
        }
    }
};

