#include<iostream>
#include<cstring>
using namespace std;
int minlen(char *str[], int n){
    int a[5],max = 0,temp=1,len;
    for(int i=0;i<n;i++){
        len = strlen(str[i]);
        if(len > max){
            max = len;
            temp = i;
        }
    }
    return temp+1;
}
int main(){
    char *str[5];
    int n;
    cin >> n;
    for(int i = 0;i < n;++i){
        char s[100];
        str[i] = new char[sizeof(char)*(strlen(s))-1];
        cin >> s;
        strcpy(str[i],s);
        cout << str[i] <<endl;
    }
    cout << minlen(str,n);
    return 0;
}