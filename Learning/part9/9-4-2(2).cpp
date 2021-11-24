#include<iostream>
using namespace std;
struct link{
    int num;
    link *next;    
};
typedef link link;
int main(){
    link *head ,*p , *rear ,*q;
    rear = new link();
    head = rear;
    head->num = 1;
    int n = 0;
    cin >> n ;
    for(int i = 2; i < n+1 ;i++){
        p = new link();
        p->num = i;
        rear->next = p;
        rear = p;
    }
    rear->next = head;
    p = head;
    while(p->next!=p){
        q = p->next;
        p = q->next;
        q->next = p->next;
        delete p;
        p = q->next;
    }
    cout << p->num;
    return 0; 
}