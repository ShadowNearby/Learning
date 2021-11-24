#include<iostream>
using namespace std;
char* Julian(int year, int day){
    cin >> year >> day;
    int sum=365;
    static char b[6];
    int a[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    char* month={"JanFebMarAprMayJunJulAugSetOctNovDec"};
    if((year%100!=0&&year%4==0)||year%400==0) {
        a[1]=29;
        sum=366;
    }
    if(day>sum) return NULL;
    b[3]=' ';
    int i;
    for(i=0;i<12;i++){
        if(day>a[i]) day-=a[i];
        else break;
    }
    if(day<10) {
        b[4] = '0';
        b[5]=day+'0';
        }
    else {
        b[4]=day/10+'0';
        b[5]=day-day/10*10+'0';
    }
        for(int j=0;j<3;j++){
        b[j]=month[i*3+j];
    }
    return b;
}
int main(){
    int year,day;
    
    //char *ans=Julian(year,day);
    cout <<Julian(year,day);
    return 0;
}
/*
Julian历法是用年以及这一年中的第几天来表示日期。设计一个函数，将Julian历法表示的日期转换成月和日，如Mar 8（注意闰年的问题）。函数返回一个字符串，即转换后的月和日。如果参数有错，如天数为第370天，返回NULL指针，此使屏幕无打印输出。

样例输入输出
样例1
input:
2020 
1
output:
Jan 01

样例2
input:
1998
33
output:
Feb 2

样例3
input:
2020 
366
output:
Dec 31

样例4
input:
2100
388
output:
*/