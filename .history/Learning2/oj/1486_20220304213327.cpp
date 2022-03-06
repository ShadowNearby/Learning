/*
 * @Date: 2022-03-04 19:32:05
 * @LastEditors: js
 * @LastEditTime: 2022-03-04 21:32:31
 * @FilePath: \code\Learning2\oj\1486.cpp
 */
#include<Stack>
#include<iostream>
#include<string>
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
    string in;
    int f = 0, t = 0;
    char ch = 0;
    bool left = false;
    cin >> in;
    int size = in.size();
    for (int i = 0; i < size; ++i)
    {
        if(str.empty()){
            str.push(ch);
        }
        else{
            switch(ch){
                case ')':
                    while(true){
                        expression.push(str.top());
                        str.pop();                       
                        if(str.top()=='&'||str.top()=='!'||str.top()=='|'){                            
                            break;
                        }                        
                    }
                    expression.push(str.top());
                    str.pop();
                    str.push(getans(expression));
                    while(!expression.empty()) {expression.pop();}
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