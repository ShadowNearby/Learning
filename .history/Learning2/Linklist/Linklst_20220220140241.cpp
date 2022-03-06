/*
 * @Date: 2022-02-20 12:45:38
 * @LastEditors: js
 * @LastEditTime: 2022-02-20 14:02:41
 * @FilePath: \code\Learning2\Linklist\Linklst.cpp
 */
#include <iostream>
class Node{
public:
    Node *next;
    int data;
    Node *move(int pos){
        Node *p = head;
        for (int i = 0; i < pos; ++i){
        p = p->next;
        }
    }
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
    int search(int value);
    int visit(int pos);
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
        delete p;
    }
    else if(pos == len - 1){
        delete p->next;
        p->next = nullptr;
    }
    else{
       Node *temp = p->next->next;
        p->next->next = nullptr;
        delete p->next;
        p->next = temp;
    }
    --len;
}
void Linklist::insert(int pos, int value){
    Node *p = head;
    for (int i = 0; i < pos - 1; ++i){
        p = p->next;
    }
    Node *temp = new Node;
    temp->data = value;
    if(pos == 0){
        head = temp;
        head->next = p;
    }
    else if(pos == len){
        temp->next = nullptr;
        p->next = temp;
    }
    else{
        temp->next = p->next;
        p->next = temp;
    }
    ++len;
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
    std::cout << std::endl;
}
void Linklist::change(int pos, int value){
    Node *p = head;
    for (int i = 0; i < pos; ++i){
        p = p->next;
    }
    p->data = value;
}
int Linklist::search(int value){
    Node *p = head;
    int pos = 0;
    while(p != nullptr){
        if(p->data == value){
            return pos;
        }
        ++pos;
        p = p->next;
    }
    return -1;
}
int Linklist::visit(int pos){
    Node *p = move(pos);
    return p->data;
}
int main(){
    Linklist linklist(5);
    for (int i = 0; i < 5; ++i){
        linklist.insert(i, i);
        linklist.print();
        linklist.del(i);
    }
    std::cout << linklist.search(4) << " ";
    return 0;
}