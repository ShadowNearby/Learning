/*
 * @Date: 2022-02-19 17:12:33
 * @LastEditors: js
 * @LastEditTime: 2022-02-20 13:27:12
 * @FilePath: \code\Learning2\part2\1.cpp
 */
#include<iostream>
using namespace std;
struct Node{
    int data;
    Node *next;
};
int main(){
    int n = 5;
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
    p = head->next;
    while(p != nullptr){
        std::cout << p->data << " ";
        p = p->next;
    }

    return 0;
}
