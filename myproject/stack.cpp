#include<iostream>
class Stack{
private:
    int *base;
    int *top;
    int size;
public:
    Stack();
    ~Stack();
    Stack &operator=(const Stack &s);
    Stack(const Stack &s);
    void append(int value);
    int gettop();
};