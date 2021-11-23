#include<iostream>
using namespace std;
struct linklist{
    int num;
    linklist *last;
    linklist *next;
    bool operator>(linklist *p);
    linklist *operator[](int i);
};
linklist *get(linklist *p){
    linklist *temp = new linklist;
    temp->num = p->num;
    temp->last = NULL;
    temp->next = NULL;
    return temp;
}
bool linklist::operator>(linklist *p){
    if(this->num > p->num){
        return true;
    }
    else
        return false;
}
void insert(linklist *last,linklist *next,int num){
    linklist *p = new linklist;
    p->next = last->next;
    p->last = next->last;
    last->next = p;
    next->last = p;
    p->num = num;
}
void insert(linklist *last,linklist *next,linklist *p){
    p->next = last->next;
    p->last = next->last;
    last->next = p;
    next->last = p;
}
void del(linklist *p){
    p->next->last = p->last;
    p->last->next = p->next;
    delete p;
    p = NULL;
}
void printall(linklist *head,linklist *tail){
    linklist *point = new linklist;
    point = head;
    while(true){
        cout << point->num << " ";
        point = point->next;
        if(point == tail){
            cout << point->num << " ";
            break;
        }
    }
    cout << endl;
}
void printall(linklist *head){
    linklist *point = new linklist;
    point = head;
    while(true){
        cout << point->num << " ";
        point = point->next;
        if(point->next == NULL){
            cout << point->next->num << " ";
            break;
        }
    }
    cout << endl;
}
void print(linklist *p){
    cout << p->num << " ";
}
void swap(linklist *a,linklist *b){
    if(a->next == b){
        linklist *t1 = b->next;
        a->last->next = b;
        b->next->last = a;
        b->next = a;
        b->last = a->last;
        a->last = b;
        a->next = t1;
    }
    else if(b->next == a){
        linklist *t1 = a->next;
        b->last->next = a;
        a->next->last = b;
        a->next = b;
        a->last = b->last;
        b->last = a;
        b->next = t1;
    }
    else{
        linklist *t1 = get(a), *t2 = get(b);
        insert(a, a->next, t2);
        insert(b, b->next, t1);
        del(a);
        del(b);
    }
}
int main(){
    linklist *head = new linklist;
    linklist *tail = new linklist;
    head->next = tail;
    head->last = NULL;
    tail->last = head;
    tail->next = NULL;
    head->num = tail->num = 0;
    int i = 1;
    linklist *p = new linklist;
    linklist *q = new linklist;
    p = head;
    while(i < 10){
        insert(p, tail, i);
        p = p->next;
        ++i;
    }
    printall(head->next, tail->last);
    printall(head->next, tail->last);
    delete p;
    delete head;
    delete tail;
    p = head = tail = NULL;
    return 0;

}