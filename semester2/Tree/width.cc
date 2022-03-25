#include <stack>
#include <iostream>
#include <vector>
#include "Tree.h"
using namespace std;
void width(Node *tree, vector<int> &num, int deep = 1){
    if(tree->left || tree->right){
        deep++;
    }
    if(tree->left){
        if(num.size() >= deep)
            num[deep - 1]++;
        else
            num.push_back(1);
        width(tree->left, num, deep);
    }
    if(tree->right){
        if(num.size() >= deep)
            num[deep - 1]++;
        else
            num.push_back(1);
        width(tree->right, num, deep);
    }
} 
void solution(Node *tree, vector<int> &num){
    stack<Node *> s;
    stack<int> p;
    Node *temp;
    int deep = 1;
    s.push(tree);
    p.push(deep);
    while(!s.empty()){
        temp = s.top();
        if(num.size() >= p.top())
            num[p.top() - 1]++;
        else
            num.push_back(1);
        s.pop();
        deep = p.top();
        p.pop();
        if(temp->left || temp->right){
            deep++;
            if(temp->left){
                p.push(deep);
                s.push(temp->left);
            }
            if(temp->right){
                p.push(deep);
                s.push(temp->right);
            }
        }
    }
}
int main()
{
    vector<int> a, b;
    int c, d;
    Tree tree(0xfffff);
    if(tree.empty()){
        cout << 0 << endl;
    }
    else{
        c = GetTickCount();
        solution(tree.root, a);
        d = GetTickCount();
    }
    for (int i = 0; i < a.size(); ++i){
        cout << a[i] << " ";
    }
    cout << d - c << endl;
    b.push_back(1);
    c = GetTickCount();
    width(tree.root, b);
    d = GetTickCount();
    for (int i = 0; i < a.size(); ++i){
        cout << b[i] << " ";
    }
    cout << d - c << endl;
    return 0;
}