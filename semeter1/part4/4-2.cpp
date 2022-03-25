#include<iostream>
using namespace std;
int main(){
    int m=0,n=0,lcm=0;
    do{
        cin >> m >> n;
    }while(m<=0||n<=0);
    lcm=m;
    while(lcm%n!=0||lcm<n)
    lcm+=m;
    cout << lcm;
    return 0; 
}