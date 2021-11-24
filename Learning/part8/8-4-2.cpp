#include<iostream>
using namespace std;
bool perfectnumber(int n){
    int sum=0;
    for(int i=1;i<n;i++){
        if(n%i==0) sum+=i;
    }
    if(sum==n) return true;
    else return false;
}
int main(){
    int m,n;
    cin >> m >> n;
    for(int j=m;j<=n;j++){
        if(perfectnumber(j)) cout << j << ' ';
        }
    return 0;

}