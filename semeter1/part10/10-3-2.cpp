#include<iostream>
#include<cstring>
using namespace std;
char *mystrrchr(char *str,char ch){
    bool flag = false;
    int len = strlen(str),temp;
    char ans[100],*a;
    temp = len;
    while(!flag&&temp>0){
        temp--;
        if(str[temp]==ch) {
            flag=true;
            break;
        }
    }
    if(flag){
        for(int i = 0;i < len - temp;i++){
            ans[i]=str[temp+i+1];
        }
        a = new char[sizeof(char)*(len-temp+1)];
        strcpy(a,ans);
        return a;
    }
    else return NULL;
}
int main(){
    char a[10000],ch,*b;
    cin >> a;
    b = new char[4*strlen(a)*2];
    strcpy(b,a);
    cin >> ch;
    cout << mystrrchr(b,ch);
    return 0;
}