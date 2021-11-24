#include <iostream>
#include <string>

using namespace std;
int getnumber(int n){
    bool flag=1;
    while(flag){
        cin >> n;
        if(n>=10&&n<=30) flag=0;
    }
    return n;
}
int main(){
    int n;
    getnumber(n);
    return 0;
}
