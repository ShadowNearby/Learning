#include<iostream>
#include<string>
using namespace std;
int main(){
    int n,a=0,b=0,c=0;
    cin >> n;
    string str[n],s;
    cin.ignore();
    for(int i=0;i<n;i++){
        getline(cin,str[i]);
        s+=str[i];
    }
    for(int j=0;j<s.size();j++){
        char temp=s[j];
        if(temp>='A'&&temp<='Z') a++;
        else if(temp>='a'&&temp<='z') a++;
        else if(temp>='0'&&temp<='9') b++;
        else if(temp!=' ')c++;
    }
    cout << "英文字母："<<a << endl<<"数字：" << b << endl<<"其他字符：" << c ;
    return 0;
}