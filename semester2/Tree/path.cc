#include "Tree.h"
#include <iostream>
#include <string>
using namespace std;
struct path{
    int length;
    string str;
};
void solution(Node *tree, path &max, path current){
    if(tree->left || tree->right){
        current.length++;        
        if(tree->left){
            current.str += "->" + to_string(tree->left->value);
            solution(tree->left, max, current);
        }
        else{
            current.str += "->" + to_string(tree->right->value);
            solution(tree->right, max, current);
        }
    }
    else{
        if(max.length < current.length){
            max.length = current.length;
            max.str = current.str;
        }
    }
}
int main(){
    Tree tree(10000);
    path ans;
    if(tree.empty()){
        cout << "NULL" << endl;
    }
    else{
        ans.length = 0;
        ans.str = to_string(tree.root->value);
        solution(tree.root, ans, ans);
    }
    cout << ans.length << endl
         << ans.str << endl;

    return 0;
}