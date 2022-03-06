/*
 * @Date: 2022-02-21 22:21:51
 * @LastEditors: js
 * @LastEditTime: 2022-02-21 22:45:32
 * @FilePath: \code\Learning2\Linklist\2-10.cpp
 */
#include "Linklist.h"
#include <iostream>
int main(){
    Linklist str1(10), str2(6);
    int len1 = 0, len2 = 0;
    Node *p, *q;
    q = str2.head;
    p = str1.head;
    while(q->next){
        q = q->next;
        p = p->next;
    }
    q->next = p->next->next->next->next;
    p = str1.head;
    while(p){
        ++len1;
        p = p->next;
    }
    p = str2.head;
    while(p){
        ++len2;
        p = p->next;
    }
    p = str1.head;
    q = str2.head;
    for (int i = 0; i < len1 - len2; ++i){
        p = p->next;
    }
    while(p != q){
        p = p->next;
        q = q->next;
    }
    Node *ans = p;
    std::cout << ans->data << " ";
    return 0;
}