/*
 * @Date: 2022-03-04 19:32:05
 * @LastEditors: js
 * @LastEditTime: 2022-03-04 20:57:22
 * @FilePath: \code\Learning2\oj\1486.cpp
 */
#include<Stack>
#include<iostream>
#include<Vector>
using namespace std;
char getans(stack<char> exp){
    if(exp.top() == '!'){
        exp.pop();
        if(exp.top() == 'f'){
            return 't';
        }
        else
            return 'f';
    }
    else if(exp.top() == '&'){
        exp.pop();
        while(!exp.empty()){
            if(exp.top() == 'f'){
                return 'f';
            }
        }
        return 't';
    }
    else{
        exp.pop();
        while(!exp.empty()){
            if(exp.top() == 't'){
                return 't';
            }
        }
        return 'f';
    }
}
int main(){
    stack<char> str,expressio;
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
                        expressio.push(str.top());
                        str.pop();
                        if(str.top()=='&'||str.top()=='!'||str.top()=='|'){
                            break;
                        }
                    }
                    str.push(getans(expressio));
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