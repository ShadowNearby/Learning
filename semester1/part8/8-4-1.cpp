#include<iostream>
using namespace std;
bool isPrime(int n){
    int i;
    for(i=2;i<n;i++){
        if(n%i==0) return false;
    }
    return true;
}
int main(){
    int m,n,count=0;
    cin >> m >> n;
    if(m==0||m==1) m=2;
    for(int j=m;j<=n;j++){
        if(isPrime(j)==true) count++;
    }
    cout << count << ' ';
    return 0;
}