#include<iostream>
#include<string>
#include<cmath>
using namespace std;
int main(void){
    string a;
    cin >> a; 
    int x=10,m=0;
    if(a[0]=='0'&&a[1]!='x') {x=8;m=1;cout << "8   "<<endl;}
    if(a[0]=='0'&&a[1]=='x') {x=16;m=2;cout << "16   "<<endl;}
    else cout << "10    " << endl;
    int num=0,y=0;
    for(int i=int(a.size())-1;i>=0+m;i--){
        num+=int(a[i]-'0')*pow(x,y);
        y++;
    }
    cout << "10    "<< num <<endl;
    int j;
    j=8;
    string ans8="";
    int temp=num;
    while(temp!=0){
        int mod=temp%j;
        temp/=j;
        if(mod<10) ans8+=char(mod+'0');
    }
    cout << j  <<  "     0";
    for(int m=int(ans8.size())-1;m>=0;m--){
        cout << ans8[m] ;
    }
    cout << endl;
    j=16;
    string ans16="";
    temp=num;
    while(temp!=0){
        int mod=temp%j;
        temp/=j;
        if(mod<10) ans16+=char(mod+'0');
        else ans16+=char(mod+'A'-10);
    }
    cout << j  <<  "    0x"   ;
    for(int m=int(ans16.size())-1;m>=0;m--){
        cout << ans16[m];
    }
    cout << endl;
    

}