#include <iostream>
#include <cstring>
using namespace std;

bool func(char array[ ], int len);

int main() {
    char ch[20];
    bool result;

    cin >> ch;

    if(func(ch, strlen(ch)-1))
        cout << "Yes";
    else
        cout << "No";

    return 0;
}

bool func(char array[ ], int len) {
    if(len<0)
        return true;
    if(*array==*(array+len)&&func(array+1,len-2))
        return true;
    else
        return false;
}
/*
本关任务：把右侧代码中的两个函数main和func填补完整，使得该程序能判断用户输入的一个正整数是否为回文数（即顺读和倒读相同的数）。

说明
1：只能在“此处填补几行代码”的位置添加代码。
2：不可定义新的变量、数组或其它对象。不可使用循环。
3：func函数的定义中不可调用库函数。
4：用户的输入必定为一串数字（少于20个字符），以回车完成输入。
5：填补部分的代码总共不超过10行（分号和逗号合计不超过10个）。

输入输出样例
样例1. input:338909833
output:Yes

样例2. input:378909833
output:No

样例3. input:8
output:Yes


*/