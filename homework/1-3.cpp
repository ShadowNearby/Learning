#include<iostream>
#include<string>
using namespace std;
char* Julian(int year, int day){
    cin >> year >> day;
    int sum=365;
    static char b[6];
    int a[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    string month{"JanFebMarAprMayJunJulAugSetOctNovDec"};
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
        b[4]=day+'0';
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