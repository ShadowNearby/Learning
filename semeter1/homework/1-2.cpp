#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int main(){
    const double eps=1E-6;
    double i=1,sum=1,m=1,x,n=1,k=0.5,temp=0.5;
    cin >> x;
    while(abs(m)>=eps){
        n*=i;
        m=temp*pow(x-1,i)/n;
        sum+=m;
        i++;
        k--;
        temp*=k;
        
    }
    cout  << sum << endl;
    return 0;
}