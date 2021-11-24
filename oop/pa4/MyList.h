#include <iostream>
using namespace std;

class mylist{
private:
    int *p;
    int len;
public:
    mylist();
    ~mylist();
    void append(int i);
    int &operator[](int i);
    friend ostream &operator<<(ostream &out, const mylist &m);

};
