#include<iostream>
#include<cmath>
using namespace std;
int main(){
    double a1=0;
    int k=0,mod=0;
    cin >> k;
    for(int i=1;i<=k-7;i++){
        for(int j=1;j<=(k-j)/2;j++){
            for(int n=1;n<=(k-i-2*j);n++) {
                if (i+2*j+5*n==k) mod++;
        }
    }
    }
    cout << mod << endl;
    return 0;

}
 