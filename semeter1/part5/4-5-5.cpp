#include<iostream>
#include<ctime>
using namespace std;
int main(){
    srand(time(0));
    int n;
    cin >> n;
    int first[n],second[n],sum[n],num[11];
    for(int j=2;j<=12;j++){
        num[j]=0;
    }
    for(int i=0;i<n;i++){
        first[i]=rand()%6+1;
        second[i]=rand()%6+1;
        sum[i]=first[i]+second[i];
    }
    for(int j=2;j<=12;j++){
        for(int i=0;i<n;i++){
        if(sum[i]==j) num[j]++;
        }
    }
    for(int j=2;j<=12;j++){
    cout << j << ":" << num[j] << endl;
    }
    return 0;
}