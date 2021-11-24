#include<iostream>
using namespace std;
bool flag(int year){
    if((year)%100!=0&&(year)%4==0||(year)%400==0) return true;
    else return false;
}
int main(){
    int n,year=1900,day=13,a[8]={0};
    cin >> n;
    int mouth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    while(year<1900+n){
        if(flag(year)) mouth[1]=29;
        else mouth[1]=28;
        for(int i=0;i<12;i++){
            for(int j=1;j<=7;j++){
                if(1+(day)%7==j) a[j]++;
            }
            day+=mouth[i];    
        }
        year++;
    }
    for(int j=1;j<=7;j++){
        cout << a[j] << " ";
    }
    return 0;
}