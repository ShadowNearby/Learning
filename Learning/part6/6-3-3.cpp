#include<iostream>
#include<string>
using namespace std;
int main(){
    string a;
    getline(cin,a);
    for(int i=0;i<a.size()-1;i++){
        for(int j=0;j<a.size()-1-i;j++){
            if(int(a[j])<int(a[j+1])){
                char temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
    cout << a[0];
    for(int i=1;i<a.size();i++){
        if(a[i]!=a[i-1])
        cout << a[i];
    }
    return 0;
}