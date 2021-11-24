#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    int n,k;
    char ch;
    cin>>n;
    string *p, *q;
    p = new string[n];
    q = new string[n];
    for (int i = 0; i < n;++i){
        cin >> p[i];
    }
    cin >> ch;
    for (int i = 0; i < n;++i){
        k = 0;
        for (int j = 0; j < 30;++j){
            if(p[i][j]==ch){
                p[i][j]=0;
            }
            else if(p[i][j]==0){
                break;
            }
        }
        for (int j = 0; j < p[i].size();++j){
            if(p[i][j]!=0){
                q[i] += p[i][j];
            }
        }
    }
    for (int i = 0; i < n-1; i++){
        for (int j = i; j < n; j++)
        {
            if (q[i] < q[j]) {
                string t = q[i];
                q[i] = q[j];
                q[j] = t;
            }
 
        }
    }
    for (int i = 0; i < n; i++){
        cout << q[i] << endl;
    }
    return 0;
}
/*
输入若干个字符串(每个字符串的长度不超过30个字符，字符串总数不超过30)，和一个英文字符ch。 要求删除每个字符串中的字符ch(区分大小写)，得到新的字符串，然后将新的字符串按照字典逆序排序后输出。

输入输出样例
input:
3
abcddc
sxwcdez
ncvccvd
c
output:
sxwdez
nvvd
abdd
*/