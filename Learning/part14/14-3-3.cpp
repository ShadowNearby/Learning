#include <iostream>
#include <string>
using namespace std;
class LongLongInt{
private:
    string num;
public:
    LongLongInt &operator+(LongLongInt &a);
    void operator=(const LongLongInt &a){
        this->num = a.num;
    }
    friend istream &operator>>(istream &is, LongLongInt &a){
        is >> a.num;
        return is;
    }
    friend ostream &operator<<(ostream &os, const LongLongInt &a){
        os << a.num;
        return os;
    }
};
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
LongLongInt &LongLongInt::operator+(LongLongInt &n1){
    string a = this->num, b = n1.num, c, ans;
    int la = a.size() , lb = b.size();
    if(la < lb){
        stringswap(a,b);
        intswap(la,lb);        
    }
    for(int i = lb-1;i<la-1;i++){
        c += '0';
    }
    c += b;
    int temp = 0;
    for(int i = la-1;i >= 0;i--){
        int m = int(a[i] - '0'), n = int(c[i] - '0');
        if(temp+m+n<10){
            ans += char(temp + m + n + '0');
            temp = 0;
        }
        else {
            ans += char(temp + m + n - 10 + '0');
            temp = 1;
        }
    }
    if(temp==1){
        ans += '1';
    }
    this->num = "";
    for(int i = ans.size()-1;i>=0;i--){
        this->num += ans[i];
    }
    return *this;
}
int main(){
    LongLongInt a, b;
    cin >> a >> b;
    cout << a << endl
         << b << endl;
    a = a + b;
    cout << a << endl;
}