/*
 * @Date: 2022-02-20 12:45:38
 * @LastEditors: js
 * @LastEditTime: 2022-02-21 14:15:14
 * @FilePath: \code\Learning2\Linklist\Linklist.h
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
    Node *move(int pos);
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
    void reverse();
    void erase(int x, int y);
    friend void merge(Linklist l,Linklist r);
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
Linklist::~Linklist(){
    while(len > 0){
        del(0);
    }
}
Node *Linklist::move(int pos){
    Node *p = head;
    for (int i = 0; i < pos; ++i){
        p = p->next;
    }
    return p;
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

void Linklist::print(){
    Node *p = this->head;
    for (int i = 0; i < len; ++i){
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
}
void Linklist::change(int pos, int value){
    Node *p = move(pos);
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
void Linklist::reverse(){
    Node *left = nullptr, *right = head->next, *mid = head;
    while(true){
        mid->next = left;
        if(right == nullptr){
            break;
        }
        left = mid;
        mid = right;
        right = right->next;
    }
    head = mid;
}
void Linklist::erase(int x, int y){
    Node *newhead = new Node;
    Node *p = newhead;
    newhead->next = head;
    while(p->next->next != nullptr){
        if(p->next->data >= x && p->next->data <= y){
            Node *temp = p->next->next;
            p->next->next = nullptr;
            delete p->next;
            p->next = temp;
        }
        else p = p->next;
    }
    if(p->next->data >= x && p->next->data <= y){
        delete p->next;
        p->next = nullptr;
    }
    head = newhead->next;
}
void merge(Linklist l,Linklist r){
    Node *p = l.head, *q = r.head;
    Node *p1 = nullptr, *q1 = nullptr, *temp = nullptr;
    while(p && q){
        p1 = p->next;
        q1 = q->next;
        p->next = q;
        q->next = p1;
        p = p1;
        q = q1;
    }
    l.len += r.len;
}