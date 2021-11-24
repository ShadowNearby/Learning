#include<iostream>
#include<string>
#include<ctime>
using namespace std;
void stringswap(string &a,string &b){
    string tem = a;
    a = b ;
    b = tem;
}
void intswap(int &a,int &b){
    int ltem = a;
    a = b;
    b = ltem;
}
string Plus(string a,string b){
    string c, ans;
    int la = a.size() , lb = b.size();
    if(la < lb){
        stringswap(a,b);
        intswap(la,lb);    
        
    }
    for(int i = lb-1;i<la-1;i++){
        c+='0';
    }
    c+=b;
    string ans;
    int temp = 0;
    for(int i = la-1;i >= 0;i--){
        int m = int(a[i]-'0') , n = int(c[i]-'0');
        if(temp+m+n<10){
            ans+=char(temp+m+n+'0');
            temp = 0;
        }
        else {
            ans+=char(temp+m+n-10+'0');
            temp = 1;
        }
    }
    if(temp==1){
        ans+='1';
    }
    c = "";
    for(int i = ans.size()-1;i>=0;i--){
        c+=ans[i];
    }
    return c;
}

string Mult(string a,string b){
    string ans="0";
    string c;
    int la = a.size() , lb = b.size();
    if(la < lb){
        stringswap(a,b);
        intswap(la,lb);
        
    }
    for(int i = lb-1;i<la-1;i++){
        c+='0';
    }
    c+=b;
    //cout << a <<endl <<c<<endl;
    for(int j=la-1;j>=0;j--){
        if(c[j]=='0') continue;
        for(int i=la-1;i>=0;i--){
            if(a[i]=='0') continue;
            string temp=to_string(int(a[i]-'0')*int(c[j]-'0'));
            for(int m=0;m<2*la-i-j-2;m++){
                temp+='0';
            }
            //cout << temp <<endl;
            ans = Plus(ans,temp);
            //cout <<ans<<endl;
        }
    }
    return ans;
}
int main(void){
    string a,b,c;
    cin >> a >> b;
    cout << Plus(a,b);
    return 0;
}