/*
 * @Date: 2022-02-20 12:45:38
 * @LastEditors: js
 * @LastEditTime: 2022-02-20 13:33:09
 * @FilePath: \code\Learning2\Linklist\Linklst.cpp
 */
#include <iostream>
class Node{
public:
    Node *next;
    int data;
};
class Linklist:public Node{
private:
    Node *head;
    int len;
public:
    Linklist(int len);
    Linklist(const Linklist &other);
    ~Linklist();
    void insert(int pos, int value);
    void del(int pos);
    void change(int pos, int value);
    bool search(int value);
    int operator[](int pos);
    void print();
};
Linklist::Linklist(int length){
    len = length;
    Node *tail, *p;
    tail = head = new Node;
    for (int i = 0; i < len; ++i){
        p = new Node;
        p->data = i;
        tail->next = p;
        tail = p;
    }
    tail->next = nullptr;
    head = head->next;
}
void Linklist::del(int pos){
    Node *p = head;
    for (int i = 0; i < pos - 1; ++i){
        p = p->next;
    }
    if(pos == 0){
        head = head->next;
        delete head;
        --len;
    }
    else if(pos == len - 1){
        delete p->next;
        p->next = nullptr;
        --len;
    }
    else{
       Node *temp = p->next->next;
        p->next->next = nullptr;
        delete p->next;
        p->next = temp;
        --len;
    }
}
Linklist::~Linklist(){
    while(len > 0){
        del(0);
    }
}
void Linklist::print(){
    Node *p = this->head;
    for (int i = 0; i < len; ++i){
        std::cout << p->data << " ";
        p = p->next;
    }
}
int main(){
    Linklist linklist(5);
    linklist.print();
    return 0;
}