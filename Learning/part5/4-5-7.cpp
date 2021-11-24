#include<iostream>
using namespace std;
int max(int a,int b){
    if(a>b) return a;
    else return b;
}
int main ( ){
    int n;
    cin >> n;
    int num[12][12]={0};
    for(int i=1;i<=n;i++){
        num[i][0]=0;
        for(int j=1;j<=i;j++)
        cin >> num[i][j];
    }
    for(int i=n-1;i>0;i--){
        for(int j=1;j<=i;j++)
        num[i][j]+=max(num[i+1][j+1],num[i+1][j]);
    }
    int maxnum=0;
    for(int j=1;j<n+1;j++){
        maxnum=max(maxnum,num[n][j]);
    }
    cout << num[1][1];
    return 0;
}