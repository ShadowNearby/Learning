#include<iostream>
#include<string>
using namespace std;
struct city{
    string name;
    int pop;
    city *next;
    void get(string n,int p){
        name = n;
        pop = p;
    }
    friend void swap(city &a,city &b){
        city temp = a;
        a = b;
        b = temp;
    }
};

typedef city city;
int main(){
    int i = 0;
    string str;
    int num;
    city *head,*rear,*p,*q;
    p = head = rear = new city();
    head->next = p;
    while(true){
        cin >> str ;
        if(str == "@") break;
        cin >> num;
        city *p = new city();
        p->get(str,num);
        rear->next = p;
        rear = p;
        
    }
    q = head;
    head = p = head->next;
    bool flag = true;
    while(flag && p->next!=p){
        flag = false;
        p = head;
        while(p->next != NULL){
            if(p->pop < p->next->pop){
                swap(p, p->next);
                flag = true;
            }
            p = p->next;
        }
    }
    p = q->next;

    while(p!=NULL){
        cout << p->name << " ";
        cout << p->pop <<endl;
        if(p->next->next==NULL){
            p->next = NULL;
            delete p->next;
            break;
        }
        p = p->next;
    }

    return 0;
}