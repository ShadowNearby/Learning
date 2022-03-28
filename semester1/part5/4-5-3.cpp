#include<iostream>
using namespace std;
int main(){
    int k,n;
    cin >> n >> k;
    int light[n];
    for(int i=1;i<=n;i++){
        light[i]=0;
    }
    for(int j=1;j<=k;j++){
        for(int i=1;i<=n;i++){
            if(i%j==0) light[i]++;
        }
    }
    for(int i=1;i<=n;i++){
        if(light[i]%2!=0) cout << i << " ";
    }
    return 0;
}