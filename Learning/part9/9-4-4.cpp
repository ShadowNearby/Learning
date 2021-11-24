#include<iostream>
#include<string>
using namespace std;
int main(void){
    string str,ans1="",ans2="";
    getline(cin,str);
    int len=int(str.size()),i=0,j=0;
    int a[7]={8,7,3,4,9,6,2};
    while(i<len){
        int tem=int(str[i])+a[j];
        if(tem<=122&&tem>=32) ans1+=char(tem);
        else ans1+=char(32+(tem-32)%(122-32+1));
        i++;
        j++;
        if(j==7) j=0;
    }
    cout << ans1 << endl;
    len=int(ans1.size());
    i=0;
    j=0;
    while(i<len){
        int tem=int(ans1[i])-a[j];
        if(tem>=32) ans2+=char(tem);
        else ans2+=char(tem+91);
        i++;
        j++;
        if(j==7) j=0;
    }
    cout << ans2;
}