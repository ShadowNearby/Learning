#include <stack>
#include <iostream>
using namespace std;
struct Node{
    int value;
    Node *left;
    Node *right;
};
class Tree{
public:
    Node *root;
    Tree(int n);
    void Create(Node *T, int n, int location = 0);
    void preOrderPrint();
    void inOrderPrint();
    bool empty();
};
void Tree::Create(Node *T, int n, int location){

    if (location * 2 + 1 > n){
        return;
    }
    if (location * 2 + 1 == n){
        T->left = new Node();
        T->left->value = location * 2 + 1;
        T->left->left = T->left->right = nullptr;
        return;
    }
    if (location * 2 + 2 == n){
        T->left = new Node();
        T->left->value = location * 2 + 1;
        T->left->left = T->left->right = nullptr;
        T->right = new Node();
        T->right->value = location * 2 + 2;
        T->right->left = T->right->right = nullptr;
        return;
    }
    T->left = new Node();
    T->left->value = location * 2 + 1;
    T->left->left = T->left->right = nullptr;
    T->right = new Node();
    T->right->value = location * 2 + 2;
    T->right->left = T->right->right = nullptr;
    Create(T->left, n, location * 2 + 1);
    Create(T->right, n, location * 2 + 2);
}
Tree::Tree(int n){
    root = new Node;
    root->value = 0;
    Create(root, n);
}
void Tree::preOrderPrint(){
    Node *q = root;
    stack<Node *> p;
    while (true){
        if (p.empty() && !q){
            break;
        }
        while (q){
            cout << q->value << " ";
            p.push(q);
            q = q->left;
        }
        q = p.top()->right;
        p.pop();        
    }
    cout << endl;
}
void Tree::inOrderPrint(){
    Node *p = root;
    stack<Node *> s;
    while(true){
        if(s.empty() && !p){
            break;
        }
        while(p){
            s.push(p);
            p = p->left;
        }
        cout << s.top()->value << " ";
        p = s.top()->right;
        s.pop();       
    }
    cout << endl;
}
bool Tree::empty(){
    if(root == nullptr){
        return true;
    }
    return false;
}