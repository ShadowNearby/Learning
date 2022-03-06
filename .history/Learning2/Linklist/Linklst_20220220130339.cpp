/*
 * @Date: 2022-02-20 12:45:38
 * @LastEditors: js
 * @LastEditTime: 2022-02-20 13:03:38
 * @FilePath: \code\Learning2\Linklist\Linklst.cpp
 */
class Node{
    Node *next;
    int data;
};
class Linklist:public Node{
private:
    Node *head;
    int len;
public:
    Linklist(int len);
    Linklist(const Linklist &other);
    ~Linklist();
    void insert(int pos, int value);
    void del(int pos);
    void change(int pos, int value);
    bool search(int value);
    int operator[](int pos);
    void print();
};
Linklist::Linklist(int len){
    int value;
}