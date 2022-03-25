#include<iostream>
#include<string>
using namespace std;
int main(){
    int n=0;
    cin >> n;
    for(int i=1;i<=200;i++){
        int tempi=i*i,temi=i;
        string ans2="0",ans1="0";
        int k1=0,k2=0;
        while(tempi!=0){
            int m=tempi%n;
            tempi/=n;
            char temp='0';
            if(m<10) temp=m+'0';
            else temp=m-10+'A';
            ans2[k1]=temp;
            k1++;
        }
        while(temi!=0){
            int m=temi%n;
            temi/=n;
            char temp='0';
            if(m<10) temp=m+'0';
            else temp=m-10+'A';
            ans1[k2]=temp;
            k2++;
        }
        int tempk=k1;
        bool flag=true;
        for(int j=0;j<k1-1;j++,k1--){
            if(ans2[j]!=ans2[k1-1]){
                flag=false;
                break;
            } 
        }
        if(flag){
            for(int j=k2-1;j>=0;j--)
            cout << ans1[j] ;
            cout << " ";
            for(int j=tempk-1;j>=0;j--)
            cout << ans2[j];
            cout << endl;
        }
    }
    return 0;
}