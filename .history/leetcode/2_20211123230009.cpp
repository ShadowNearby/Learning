/*
 * @Date: 2021-11-23 22:51:01
 * @LastEditors: js
 * @LastEditTime: 2021-11-23 22:59:43
 * @FilePath: \code\leetcode\2.cpp
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *ans = new ListNode;
        ListNode *p, *rear;
        ans = rear;
        while(l1 != nullptr && l2 != nullptr){
            p = new ListNode(l1->val + l2->val);
            p = rear->next;
            p = rear;
            l1 = l1->next;
            l2 = l2->next;
        }
        while(l1 != nullptr){
            p = new ListNode(l1->val);
            p = rear->next;
            p = rear;
            l1 = l1->next;
        }
        while(l2 != nullptr){
            p = new ListNode(l2->val);
            p = rear->next;
            p = rear;
            l2 = l2->next;
        }
        rear->next = nullptr;
        p = ans->next;
        while(p->next != nullptr){
            if(p->val >= 10){
                p->val %= 10;
                ++p->next->val;
            }
            p = p->next;
        }
        if(p->val >= 10){
            
        }
    }
};