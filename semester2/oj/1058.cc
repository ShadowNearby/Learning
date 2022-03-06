/*
 * @Date: 2022-02-27 17:43:20
 * @LastEditors: js
 * @LastEditTime: 2022-02-27 20:17:40
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
        head->value = -1;
    }
    NODE* move(int i) {
        NODE *p = head;
        for (int j = 0; j < i + 1; ++j){
            p = p->next;
        }
        return p;
    }
    void insert(int i, int x) {
        NODE *p = move(i - 1);
        NODE *temp = new NODE;
        temp->value = x;
        temp->next = p->next;
        p->next = temp;
        ++len;
    }
    void remove(int i) {
        NODE *p = move(i - 1);
        NODE *temp = p->next->next;
        delete p->next;
        p->next = temp;
        --len;
    }
    void remove_insert(int i) {
        NODE *p = move(i);
        insert(len, p->value);
        remove(i);
    }
    void get_length() {
        cout << len << endl;
    }
    void query(int i) {
        if(i > len){
            cout << -1 << endl;
        }
        else{
            NODE *p = move(i);
            cout << p->value << endl;
        }
    }
    void get_max() {
        if(len == 0){
            cout << -1 << endl;
        }
        else{
            int max = 0;
            NODE *p = head;
            for (int i = 0; i <= len; ++i){
                if(p->value > max){
                    max = p->value;
                }
                p = p->next;
            }
            cout << max << endl;
        }
        
    }
    void clear() {
        while(len > 0){
        remove(0);
        }
        delete head;
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