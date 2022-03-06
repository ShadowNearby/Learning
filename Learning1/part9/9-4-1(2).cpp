#include<iostream>
using namespace std;
int main(){
    char a[20];
    char b[20];
    char t;
    cin.getline(a, 20);
    cin.getline(b, 20);
    for (int i = 0; i < 20;i++){
        if(a[i]==0||b[i]==0)
            continue;
        t = a[i];
        a[i] = b[i];
        b[i] = t;
    }
    for (int i = 0; i < 20;i++){
        if(a[i]==0)
            break;
        cout << a[i];
    }
    cout << endl;
    for (int i = 0; i < 20;i++){
        if(b[i]==0)
            break;
        cout << b[i];
    }
    return 0;
}