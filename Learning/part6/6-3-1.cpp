#include<iostream>
#include<string>
using namespace std;
int main(){
    string b="AEIOUaeiou";
    int n=0;
    char a[80];
    for(int i=0;i<80;i++){
        a[i]=' ';
    }
    cin.getline(a,80,'\n');
    for(int i=0;i<80;i++){
        for(int j=0;j<10;j++){
            if(a[i]==b[j]) n++;
        }
    }
    cout << n << endl;
    return 0;
}