#include<iostream>
#include<string>
using namespace std;
int main(){
    string a;
    string b;
    int temi=-1;
    getline(cin,a);
    getline(cin,b);
    //cin.getline(b,1,'\n');
    for(int i=0;i<80;i++){
        if(a[i]==b[0]) temi=i;
    }
    if(temi==-1) cout << "Not Found" << endl;
    else cout << temi << endl;
    return 0;
}
