#include<iostream>
using namespace std;
int main(){
    long long n = 0;
    cin >> n;
    long long a = 0, b = 0, c = 0;
    for (a = 1; a < n; ++a){
        for (b = a; b < n; ++b){
            for (c = b; c < n; ++c){
                if( a * b * c == 2 * (a + b + c)){
                    cout << a << " " << b << " "<< c << endl;
                }
            }
        }
    }
    return 0;
}