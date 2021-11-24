/*
 * @Author: your name
 * @Date: 2021-11-21 22:08:39
 * @LastEditTime: 2021-11-22 14:56:56
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \code\leetcode\21.cpp
 */
#include <iostream>
// Definition for singly-linked list.
struct ListNode {
 int val;
 ListNode *next;
 ListNode() : val(0), next(nullptr) {}
 ListNode(int x) : val(x), next(nullptr) {}
 ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *head = new ListNode;
        ListNode *p = head;
        while(l1 != nullptr && l2 != nullptr){
            if(l1->val <= l2->val){
                l1->next = mergeTwoLists(l1->next, l2);
                return l1;
            }
            else{
                l2->next = mergeTwoLists(l1, l2->next);
                return l2;
            }
        }
        if(l1 == nullptr){
            return l2;
        }
        else{
            return l1;
        }
    }
};
int main(){
    Solution a;
    ListNode *l1 = new ListNode;
    ListNode *l2 = new ListNode;
    ListNode *rear, *p;
    rear = l1;
    l1->val = 1;
    for (int i = 0; i < 5; ++i){
        p = new ListNode(3 + i);
        rear->next = p;
        rear = p;
    }
    rear->next = nullptr;
    rear = l2;
    l2->val = 1;
    for (int i = 0; i < 5; ++i){
        p = new ListNode(10 + i);
        rear->next = p;
        rear = p;
    }
    rear->next = nullptr;
    print(l1);
    print(l2);
    ListNode *ans = a.mergeTwoLists(l1, l2);
    print(ans);
    return 0;
}
/* 迭代
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *head = new ListNode;
        ListNode *p = head;
        while(l1 != nullptr && l2 != nullptr){
            if(l1->val <= l2->val){
                p->next = l1;
                l1 = l1->next;
            }
            else{
                p->next = l2;
                l2 = l2->next;
            }
            p = p->next;
        }
        if(l1 == nullptr){
            p->next = l2;
        }
        else{
            p->next = l1;
        }
        return head->next;
    }
    
}; */
/* 递归
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *head = new ListNode;
        ListNode *p = head;
        while(l1 != nullptr && l2 != nullptr){
            if(l1->val <= l2->val){
                l1->next = mergeTwoLists(l1->next, l2);
                return l1;
            }
            else{
                l2->next = mergeTwoLists(l1, l2->next);
                return l2;
            }
        }
        if(l1 == nullptr){
            return l2;
        }
        else{
            return l1;
        }
    }
}; */