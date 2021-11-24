#include<iostream>
using namespace std;
int main(){
    double fee=0;
    int du=0,yaun=0,jiao=0;
    cin >> du ;
    fee = du * 0.6;
    cout << fee << " " << int(fee) <<" "<< (fee-int(fee))*10 << endl;
    return 0;
}