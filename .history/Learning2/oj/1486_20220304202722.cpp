/*
 * @Date: 2022-03-04 19:32:05
 * @LastEditors: js
 * @LastEditTime: 2022-03-04 20:27:22
 * @FilePath: \code\Learning2\oj\1486.cpp
 */
#include<Stack>
#include<iostream>
#include<Vector>
using namespace std;
char getans(vector exp){

}
int main(){
    vector<char> exp;
    stack<char> str;
    int f = 0, t = 0;
    char ch = 0;
    bool left = false;
    while(cin >> ch){
        if(str.empty()){
            str.push(ch);
        }
        else{
            switch(ch){
                case '(':
                    str.push(ch);
                    break;
                case ')':
                    while(str.top() != '('){
                        exp.push_back(str.top());
                        str.pop()
                    }                    
                    str.pop();
                    str.push(getans(exp));
                    exp.clear();
                    break;
                case ',':
                    break;
                case ''
            }
        }

    }
}