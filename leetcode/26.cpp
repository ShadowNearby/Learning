/*
 * @Date: 2021-11-22 21:25:24
 * @LastEditors: js
 * @LastEditTime: 2021-11-22 21:59:44
 * @FilePath: \code\leetcode\26.cpp
 */
#include <vector>
#include<iostream>
using namespace std;
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int len = nums.size();
        if(len == 0){
            return 0;
        }
        int i = 1, j = 1;
        while(i < len){
            if(nums[i] != nums[i - 1]){
                nums[j] = nums[i];
                ++j;
            }
            ++i;
        }
        return j;
    }
};

