#include<iostream>
#include<string>
using namespace std;
struct student{
    int id;
    string name;
    char sex;
    int age;
    int clas;
    int english;
    int math;
    int physics;
    int sum;
    int rank;
    student *next;
};
void swap(student a,student b){
    //lazy
}
void get(student *p){
    cin >> p->id << p->name << p->sex << p->age << p->clas << p->english << p->math << p->physics ;
}
void print(student *a){
    cout << "id : " << a->id << endl;
    cout << "name : " << a->name << endl;
    cout << "sex : " << a->sex << endl;
    cout << "age : " << a->age << endl;
    cout << "class : " << a->clas << endl;
    cout << "english : " << a->english << endl;
    cout << "math : " << a->math << endl;
    cout << "physics : " << a->physics << endl;
    cout << "sum : " << a->sum << endl;
}
void printall(student *head){
    while(head!=NULL){
        print(head);
        head = head->next;
    }
}
void add(student *head){
    while(head->next!=NULL){
        head = head->next;
    }
    student *p;
    get(p);
    head->next = p;
}
void del(student *head){
    while(head->next->next!=NULL){
        head = head->next;
    }
    delete head->next;
    head->next = NULL;
}
void eachsum(student *head){
    while(head->next!=NULL){
        head->sum = head->english + head->math + head->physics;
        cout << "sum = " << head->sum;
        head = head->next;
    }
}
void ranking(student *head){
    bool flag = true;
    student *p;
    p = head;
    while(flag){
        head = p;
        while(head->next!=NULL){
            if(head->english < head->next->english){
                swap(head, head->next);
            }
        }
    }
    head = p;
    while(head->next->next!=NULL){
        cout << head->name;
        head = head->next;
    }
}
int main(){
    student *head, *rear, *p, *q;
    head = rear = p = new student();
    head->next = p;
    for (int i = 0; i < 10;i++){
        student *p = new student();
        //cin >> p->id << p->name << p->sex << p->age << p->clas << p->english << p->math << p->physics ;
        rear->next = p;
        rear = p;
    }
    head = head->next;
    printall(head);
    return 0;
}