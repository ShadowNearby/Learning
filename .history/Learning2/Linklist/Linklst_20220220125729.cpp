/*
 * @Date: 2022-02-20 12:45:38
 * @LastEditors: js
 * @LastEditTime: 2022-02-20 12:57:29
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
    insert(int pos, int value);
    del(int pos);
    change(int pos, int value);
    
};