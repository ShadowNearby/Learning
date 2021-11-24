#include <iostream>
using namespace std;

void deletechar(char* str1, const char* str2) {
	//在此处补全代码
}

int main() {
	char str1[80]={'\0'};
    char str2[80]={'\0'};
	cin.getline(str1,80);
    cin.getline(str2,80);
	deletechar(str1, str2);

    cout<<str1<<endl;
	return 0;
}
/*
设计一个函数void deletechar(char *str1, const char *str2)，在str1中删除str2中出现的字符。用递归实现

输入输出样例
样例1
input:
Iwannarock
rock
output:
Iwanna

样例2
input:
small dog little eyes
dog
output:
small  little eyes
*/