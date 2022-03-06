/*
 * @Date: 2022-02-20 14:08:00
 * @LastEditors: js
 * @LastEditTime: 2022-02-21 14:22:35
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
    while(right){
        mid->next = left;
        
    }
    return 0;
}