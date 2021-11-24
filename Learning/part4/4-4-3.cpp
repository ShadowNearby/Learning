#include<iostream>
#include<cmath>
using namespace std;
int main(){
    long long sum=0,n[11];
    n[0]=1;
    for(int i=1;i<11;i++){
        n[i] = n[i-1]*i;
        sum = sum + n[i];
    }
    cout << sum << endl;
    return 0;
}