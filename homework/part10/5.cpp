#include <iostream>
using namespace std;

void deletechar(char* str1, const char* str2) {
    char *temp = new char[80];

    for (int k = 0; k < 80;k++){
        temp[k] = str1[k];
        str1[k] = 0;
    }
    int i = 0, j = 0;
    while(*(str2+j)!=0){
        i = 0;
        while(*(temp+i)!=0){
            if(*(str2+j)==*(temp+i)){
                temp[i] = '@';
            }
            ++i;
        }
        ++j;    
    }
    i = 0;
    for (int k = 0; k < 80;k++){
        if(temp[k] != '@')
            str1[i++] = temp[k];
    }
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
设计一个函数void deletechar(char *str1, const char *str2)，在str1中删除str2中出现的字符。用非递归方法实现。

输入输出样例
input:
Iwannarock
rock
output:
Iwanna
*/