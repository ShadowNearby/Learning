/*
 * @Date: 2022-02-20 14:17:17
 * @LastEditors: js
 * @LastEditTime: 2022-02-20 14:41:50
 * @FilePath: \code\Learning2\oj\linklist.cpp
 */
# include <iostream>
# include <stdio.h>
using namespace std;
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
    Linklist(int len, int *arr);
    ~Linklist();
    void insert(int pos, int value);
    void del(int pos);
    void change(int pos, int value);
    int search(int value);
    int visit(int pos);
    int getlen() { return len; }
    void print();
    void swap();
};
Linklist::Linklist(int length, int *arr){
    len = length;
    Node *tail, *p;
    tail = head = new Node;
    for (int i = 0; i < len; ++i){
        p = new Node;
        p->data = arr[i];
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
void Linklist::swap(){
    Node *p = head;
    while()
}

int main() {
  int n, *a;
  cin >> n;
  a = new int [n];
  for (int i = 0; i < n; ++ i) cin >> a[i];
  Linklist linklist(n, a);
  delete [] a;
  int m, op, i, x;
  cin >> m;
  while(m --) {
    cin >> op;
    switch(op) {
      case 1: 
        cin >> i >> x;
        if(i >= 0 && i <= linklist.getlen())
        linklist.insert(i, x);
          break;
      case 2:
        cin >> i;
        if(i >= 1 && i <= linklist.getlen())
        linklist.del(i - 1);
        break;
      case 3:
        L.EvenOddSwap();
           break;
      case 4:
        cin >> i;
        linklist.visit(i - 1);
        break;
      case 5:
        linklist.print();
        break;
    }
  }

  while(linklist.len > 0){
    linklist.del(0);
  }

  return 0;
}