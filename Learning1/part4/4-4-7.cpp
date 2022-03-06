#include<iostream>
#include<cmath>
using namespace std;
int main(){
    double n=0;
    cin >> n;
    for(double i= 2; i < n ;i++){
        double sum=0;
        for(double j = 1;j <= i; j++){
        sum = sum + (sqrt(1-(j/i)*(j/i))+sqrt(1-((j-1)/i)*((j-1)/i)))/(2*i);
        }
        cout << sum*4 << endl;
    }
    
    return 0;
}