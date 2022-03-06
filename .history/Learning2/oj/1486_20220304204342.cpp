/*
 * @Date: 2022-03-04 19:32:05
 * @LastEditors: js
 * @LastEditTime: 2022-03-04 20:43:42
 * @FilePath: \code\Learning2\oj\1486.cpp
 */
#include<Stack>
#include<iostream>
#include<Vector>
using namespace std;
int main(){
    stack<char> str, exp;
    int f = 0, t = 0;
    char ch = 0;
    bool left = false;
    while(cin >> ch){
        if(str.empty()){
            str.push(ch);
        }
        else{
            if(ch >= '0' && ch <= '9'){
                str.push(ch);
            }
            switch(ch){
                case '(':
                    str.push(ch);
                    break;
                case ')':
                    while(true){
                        exp.push(str.top());
                        str.pop();
                        if(str.top()=='&'||str.top()=='!'||str.top()=='|'){
                            break;
                        }
                    }
                    if(exp.top() == '!'){
                        exp.pop();
                        if(exp.top() == 'f'){
                            str.push('t');
                        }
                        else
                            str.push('f');
                    }
                    else if(exp.top() == '&'){
                        exp.pop();
                        while()
                    }
                    
                    break;
                case ',':
                    break;
                case '&', '!', '|':
                    str.push(ch);
            }
        }

    }
}