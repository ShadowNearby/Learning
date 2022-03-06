/*
 * @Date: 2022-02-27 17:43:20
 * @LastEditors: js
 * @LastEditTime: 2022-02-27 18:11:41
 * @FilePath: \code\Learning2\oj\1058.cc
 */
#include <iostream>
#include <cstdio>
using namespace std;

namespace LIST
{

    struct NODE {
        NODE *next;
        int value;
    };

    NODE *head = nullptr;
    int len = 0;

    void init() {
        len = 0;
        head = new NODE;
        head->next = head;
    }
    NODE* move(int i) {
        NODE *p = head;
        for (int j = 0; j < i; ++j){
            p = p->next;
        }
        return p;
    }
    void insert(int i, int x) {
        NODE *p = move(i);
        NODE *temp = new NODE;
        temp->value = x;
        temp->next = p->next;
        p->next = temp;
        ++len;
    }
    void remove(int i) {
        --len;
        NODE *p = move(i - 1);
        NODE *temp = p->next->next;
        delete p->next;
        p->next = temp;
    }
    void remove_insert(int i) {
        NODE *p = move(i - 1);
        insert(len, p->next->value);
        remove(i);
    }
    void get_length() {
        cout << len << endl;
    }
    void query(int i) {
        if(i > len){
            return -1;
        }
    }
    void get_max() {
        // TODO
    }
    void clear() {
        while(len > 0){
        remove(0);
    }
    }

}
int n;
int main()
{
    cin >> n;
    int op, x, p;
    LIST::init();
    for (int _ = 0; _ < n; ++_)
    {
        cin >> op;
        switch(op) {
            case 0:
                LIST::get_length();
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p,x);
                break;
            case 2:
                cin >> p;
                LIST::query(p);
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                cin >> p;
                LIST::remove_insert(p);
                break;
            case 5:
                LIST::get_max();
                break;
        }
    }
    LIST::clear();
    return 0;
}