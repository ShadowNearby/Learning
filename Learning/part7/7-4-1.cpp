#include<iostream>
using namespace std;
char getUChar(){
    bool flag=1;
    char a;
    while(flag){
        cin >> a;
        if(!(a>='A'&&a<='Z')) {
        flag=1;
        cout << "please do again" << endl;
        }
    else flag=0;
    }
    return a;
}
int main(){
    cout << getUChar();
    return 0;
}
