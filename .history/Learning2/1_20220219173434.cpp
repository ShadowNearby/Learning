/*
 * @Date: 2022-02-19 17:12:33
 * @LastEditors: js
 * @LastEditTime: 2022-02-19 17:34:33
 * @FilePath: \code\Learning2\1.cpp
 */
#include<iostream>
using namespace std;
struct Node{
    int data;
    Node *next;
};
int main(){
    int n = 2;
    Node *head, *tail, *p;
    head = new Node;
    tail = head;
    for (int i = 0; i < n; ++i){
        p = new Node;
        p->data = i;
        tail->next = p;
        tail = p;
    }
    tail->next = nullptr;
    Node *pre = nullptr, *next = nullptr, *temp = nullptr;
    pre = head->next;
    next = pre->next;
    while(next != nullptr){
        temp = next->next;
        next->next = pre;
        pre = next;
        next = temp;
    }

    return 0;
}
