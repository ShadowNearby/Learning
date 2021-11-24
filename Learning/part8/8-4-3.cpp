#include<iostream>
#include<string>
#include<cmath>
using namespace std;
void printint(int n,int base){
    string ans2="";
        int k1=0;
        while(n!=0){
            int m=n%base;
            n/=base;
            char temp='0';
            if(m<10) temp=m+'0';
            else temp=m-10+'A';
            ans2+=temp;
            k1++;
        }
        for(int i = ans2.size() - 1 ; i>=0 ; i--){
            cout << ans2[i] ;
        }
    
}
int main(){
    int m,n;
    cin >> m >> n;
    printint(m,n);
    return 0;
}