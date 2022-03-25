#include<iostream>
#include<ctime>
using namespace std;
int main(){
    srand(time(NULL));
    int num=rand()%99+1;
    int a;
    bool flag=0;
    while(!flag){
        cin >> a;
        if(a<num) cout << "low" << endl;
        else if(a>num) cout << "high" << endl;
        else if(a==num) {
            flag=1;
            cout << "right" << endl;}
    }
    return 0;
}