/*
 * @Date: 2022-03-04 19:32:05
 * @LastEditors: js
 * @LastEditTime: 2022-03-04 21:13:13
 * @FilePath: \code\Learning2\oj\1486.cpp
 */
#include<Stack>
#include<iostream>
#include<Vector>
using namespace std;
char getans(stack<char> &exp){
    int f = 0, t = 0;
    while(exp.top() != 'f' && exp.top() != 't'){
        if(exp.top()== 'f'){
            ++f;
        }
        else
            ++t;
        exp.pop();
    }
    if(exp.top() == '!'){
        exp.pop();
        if(t == 0){
            return 't';
        }
        else
            return 'f';
    }
    else if(exp.top() == '&'){
        if(f == 0)
            return 't';
        else return 'f';
    }
    else{
        if(t == 0){
            return 'f';
        }
        else
            return 't';
    }
}
int main(){
    stack<char> str,expression;
    int f = 0, t = 0;
    char ch = 0;
    bool left = false;
    while(cin >> ch){
        if(str.empty()){
            str.push(ch);
        }
        else{
            switch(ch){
                case ')':
                    while(true){
                        expression.push(str.top());                       
                        if(str.top()=='&'||str.top()=='!'||str.top()=='|'){
                            str.pop();
                            break;
                        }
                        str.pop();
                    }
                    str.push(getans(expression));
                    exp.pop();
                    break;
                case ',':case '(':
                    break;
                case '&':case '!':case '|':case 'f':case 't':
                    str.push(ch);
                    break;
            }
        }
    }
    if(str.top() == 'f'){
        cout << 0;
    }
    else
        cout << 1;
}