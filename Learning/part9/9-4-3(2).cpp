#include<iostream>
using namespace std;
int main(){
    char *head = new char[100];
    cin.getline(head, 100);
    char **p = new char *[11];
    int j = 0, num = 0;
    for (int i = 0; i < 100;i++){
        if (*(head + i) == 0&&*(head + i - 1) == 0) {
            break;
        }
        else if(*(head+i) == ' '||*(head+i) == 0){
            num++;
            char *a = new char [j+1];
            for (int m = 0; m < j;++m){
                *(a + m) = *(head + i - j + m);
            }
            *(a + j) = '\0';
            p[num] = a;
        
            j = 0;
        } 
        else{
            j++;
        }
    }
    cout << num << endl;
    char *q;
    q = new char[10];
    cin.getline(q, 10);
    for (int i = 0; i < 10;i++){
        if(*(q+i)==0){
            break;
        }
        int n = int(*(q + i) - '0')+1;
        cout << p[n] << " ";
    }
    return 0;
}