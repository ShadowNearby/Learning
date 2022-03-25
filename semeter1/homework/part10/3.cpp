#include <iostream>
#include<cstring>
using namespace std;

//请在此处定义getDate函数，main函数内容不要更改
void getDate(int &a,int &b,int &c){
    char date[10], mon[3], *p = {"JanFebMarAprMayJunJulAugSetOctNovDec"};
    cin >> date;
    int len = strlen(date),ti;
    for (int i = 0; i < len;++i){
        if(date[i]=='-'){
            ti = i;
            break;
        }
    }
    if(ti==1){
        a = int(date[0] - '0');
        if(date[7]==0){
            c = int(date[6] - '0');
        }
        else {
            c = 10 * int(date[6] - '0') + int(date[7] - '0');
        }
    }
    else {
        a = int(date[1] - '0') + int(date[0] - '0') * 10;
        if(date[8]==0){
            c = int(date[7] - '0');
        }
        else {
            c = 10 * int(date[7] - '0') + int(date[8] - '0');
        }
    }
    for (int i = 0; i < 36;i+=3){
        if(date[ti+1]==p[i]&&date[ti+2]==p[i+1]&&date[ti+3]==p[i+2]){
            b = i / 3 + 1;
        }
    }
}
int main()
{
    int day, month, year;
    getDate(day,month,year);
    cout<<" "<<day<<" "<<month<<" "<<year<<endl;
    return 0;
}
/*
写一个函数getDate，从键盘读入一个形如dd-mmm-yy的日期。其中dd是一个1位或2位的表示日的整数，mmm是月份的3个字母的缩写，yy是两位数的年份。函数读入这个日期，并将它们以数字形式传给3个参数。

输入输出样例
样例1
input:5-Mar-18
output:5 3 18

样例2
input:12-Mar-18
output:12 3 18
*/