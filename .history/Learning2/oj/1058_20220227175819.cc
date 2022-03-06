/*
 * @Date: 2022-02-27 17:43:20
 * @LastEditors: js
 * @LastEditTime: 2022-02-27 17:58:19
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
        head->next = head;
    }
    NODE* move(int i) {
        NODE *p = head->next;
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
    }
    void remove(int i) {
        // TODO
    }
    void remove_insert(int i) {
        //TODO
    }
    void get_length() {
        // TODO
    }
    void query(int i) {
        // TODO
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