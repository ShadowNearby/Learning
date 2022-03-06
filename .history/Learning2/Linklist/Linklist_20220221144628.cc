/*
 * @Date: 2022-02-20 14:08:00
 * @LastEditors: js
 * @LastEditTime: 2022-02-21 14:46:28
 * @FilePath: \code\Learning2\Linklist\Linklist.cc
 */
#include "Linklist.h"
#include <iostream>
int main(){
    int n;
    std::cin >> n;
    Linklist a(n);
    Node *mid = a.head;
    for (int i = 0; i < -1 + n / 2; ++i){
        mid = mid->next;
    }
    a.len /= 2;
    Linklist b;
    b.head = mid->next;
    mid->next = nullptr;
    b.len = n / 2;
    mid = b.head;
    Node *left = nullptr, *right = mid->next;
    while(true){
        mid->next = left;
        if(right == nullptr){
            break;
        }
        left = mid;
        mid = right;
        right = right->next;
    }
    b.head = mid;
    left = a.head;
    right = b.head;
    Node *a1 = nullptr, *a2 = nullptr;
    while(left && right){
        a1 = left->next;
        a2 = right->next;
        right->next = left;
        left->next = a2;
        right = a2;
        left = a1;
    }
    Node *p = b.head;
    while(p){
        std::cout << p->data <<" ";
        p = p->next;
    }
    return 0;
}