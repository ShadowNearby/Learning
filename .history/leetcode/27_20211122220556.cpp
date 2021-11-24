/*
 * @Date: 2021-11-22 22:02:31
 * @LastEditors: js
 * @LastEditTime: 2021-11-22 22:05:56
 * @FilePath: \code\leetcode\27.cpp
 */
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int len = nums.size();
        int i = 0, j = 0;
        while(j < len){
            if(nums[j] != val){
                nums[i] = nums[j];
                ++i;
            }
            ++j;
        }
        return i;
    }
};