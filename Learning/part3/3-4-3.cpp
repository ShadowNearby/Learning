#include<iostream>
using namespace std;
int main(){
    double n,m;
    cin >> n >> m ;
    double r=(m-2*n)/2;double c=(4*n-m)/2;
    if((r-int(r)==0)&&r>=0&&(c-int(c)==0)&&c>=0){
        cout << "chicken ="<<c <<" rabit ="<<  r << endl;
    }
    else {
        cout << "none" << endl;
    }
    return 0;
}