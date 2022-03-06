/*
 * @Date: 2022-03-04 19:32:05
 * @LastEditors: js
 * @LastEditTime: 2022-03-04 20:37:49
 * @FilePath: \code\Learning2\oj\1486.cpp
 */
#include<Stack>
#include<iostream>
#include<Vector>
using namespace std;
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
            if(ch >= '0' && ch <= '9'){
                str.push(ch);
            }
            switch(ch){
                case '(':
                    str.push(ch);
                    break;
                case ')':
                    while(true){
                        exp.push_back(str.top());
                        str.pop();
                        if(str.top()=='&'||str.top()=='!'||str.top()=='|'){
                            break;
                        }
                    }
                    if(exp.back() == '!'){
                        exp.pop_back();
                        if(exp.back() == 'f'){
                            str.push('')
                        }
                    }
                    exp.clear();
                    break;
                case ',':
                    break;
                case '&', '!', '|':
                    str.push(ch);
            }
        }

    }
}