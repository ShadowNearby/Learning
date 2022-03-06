/*
 * @Date: 2022-02-20 12:45:38
 * @LastEditors: js
 * @LastEditTime: 2022-02-20 12:58:39
 * @FilePath: \code\Learning2\Linklist\Linklst.cpp
 */
struct Node{
    Node *next;
    int data;
};

class Linklist{
private:
    Node *head;
    int len;

public:
    Linklist(int len);
    ~Linklist();
    void insert(int pos, int value);
    void del(int pos);
    void change(int pos, int value);
    bool search(int value)
};