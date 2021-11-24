#include "MyList.h"
mylist::mylist(){
    p = NULL;
    len = 0;
}
mylist::~mylist(){
    len = 0;
    delete[] p;
    p = NULL;
}
void mylist::append(int i){
    ++len;
    p = new int[len];
    *(p + len - 1) = i;
}
int &mylist::operator[](int i){
    return *(p + i);
}
ostream &mylist::operator<<(ostream &out,const mylist &m){
    for (int i = 0; i < m.len;i++){
        cout << *(m.p + i) << " ";
    }
    return out;
}