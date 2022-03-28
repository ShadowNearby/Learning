#include<iostream>
using namespace std;
int main(void){
    int n;
    cin >> n;
    bool flag[1000];
    for(int i=1;i<=n;i++){
        flag[i]=1;
    }
    int mod=n,imax=n,count=0;
    while(mod>1){
    for(int i=1;i<=imax;i++){
        if(flag[i]!=0) {
            count++;
        }
        if(count==3){
            count=0;
            flag[i]=0;
            mod--;
        }
    }
        for(int j=n;j>=1;j--){
            if(flag[j]!=0) {
            imax=j;
            break;
            }
        }
    }
    for(int i=1;i<n+1;i++){
        if(flag[i]==1) cout << i << ' ';
    }

}