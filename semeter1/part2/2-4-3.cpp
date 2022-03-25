#include <iostream>
using namespace std;
int main(){
    int a=0;
    cin >> a;
    cout << a/100 << " " << int(a%100/10) << " " << a%10 << endl ;
    return 0;
}