#include<iostream>
#include<string>
using namespace std;
int main(){
    string a;
    bool flag=0;
    while(cin >> a)
    {
        if(int(a.size()!=12)) {
            cout << "please try again" <<endl ; continue;
        }
        for(int i=0;i<12;i++){
        if(i!=3){
            if(!(a[i]>='0'&&a[i]<=9)) {
                    cout << "please try again" <<endl ;break;continue;
            }
        }
            if(i==3) {
                if(a[i]!='-') {
                    cout << "please try again" <<endl ;break;continue;
                }
            }
        }
        cout << a;
        break;
    }
    return 0;
}