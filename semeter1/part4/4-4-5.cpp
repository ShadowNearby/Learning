#include<iostream>
#include<cmath>
#include<string>
#include<ctime>
using namespace std;
int main(){
    srand(time(0));
    int a[3],b[3];
    bool flag=0;
    while(flag==0){
        for(int i=0;i<3;i++){
        a[i]=rand()%10;}{
        if(a[0]!=a[1]&&a[2]!=a[1]&&a[0]!=a[2]) flag=1;}}
    int times=7;
    while(times>0){
        int m=0;
    for(int i=0;i<3;i++){
        cin >> b[i];}
    for(int i=0;i<3;i++){
        if(a[i]==b[i]) m++;}
    if(m==3) { cout<< "3A0B" << endl <<"right" <<  endl;break;}
    if(m==2) { cout<< "2A0B" << endl ;}
    if(m==1) {   
        int n=0;
        for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
    if(a[i]==b[j]) n++;}cout << "1A" << n-1 << "B" <<endl;}
    if(m==0){
        int n=0;
        for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
    if(a[i]==b[j]) n++;}cout << "0A" << n << "B" <<endl;}
    times--;
    }
    if(times==0){
        cout << "fail" << endl;
    }
    return 0;
}
