#include <iostream>
#include <string>
using namespace std;
string str ;
int main(){
    cin >> str ;
    for(int i = 0; i < str.size() ; i++){
    char a = int(str[i])+29;
    cout << a ;
    }
    return 0;
}//str[0]