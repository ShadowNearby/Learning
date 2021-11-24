#include<iostream>
using namespace std;
class ploy{
public:
    int num;
    int times;
    ploy *next;
    ploy *operator+(const ploy *p);
};
ploy *ploy::operator+(const ploy *p){
    ploy *p1 = this->next, *p2 = p->next;
    ploy *head = new ploy;
    ploy *rear, *ans;
    rear = head;
    while(p1 != NULL && p2 != NULL){
        ans = new ploy;
        if(p1->times < p2->times){
            ans->times = p1->times;
            ans->num = p1->num;
            p1 = p1->next;
        }
        else if(p1->times > p2->times){
            ans->times = p2->times;
            ans->num = p2->num;
            p2 = p2->next;
        }
        else{
            ans->times = p1->times;
            ans->num = p1->num + p2->num;
            p1 = p1->next;
            p2 = p2->next;
        }
        rear->next = ans;
        ans = rear;
    }
    while(p1 != NULL){
        ans = new ploy;
        ans->times = p1->times;
        ans->num = p1->num;
        p1 = p1->next;
        rear->next = ans;
        ans = rear;
    }
    while(p2 != NULL){
        ans = new ploy;
        ans->times = p2->times;
        ans->num = p2->num;
        p2 = p2->next;
        rear->next = ans;
        ans = rear;
    }
    ans->next = NULL;
    return head;
}