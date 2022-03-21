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
    Node *current, *temp;
    int deep = 1;
    s.push(tree);
    p.push(deep);
    while(!s.empty()){
        temp = s.pop();
    }
}
int main()
{
    vector<int> a;
    Tree tree(1022);
    if(tree.empty()){
        cout << 0 << endl;
    }
    else{
        a.push_back(1);
        width(tree.root, a);
    }
    for (int i = 0; i < a.size(); ++i){
        cout << a[i] << " ";
    }
    return 0;
}