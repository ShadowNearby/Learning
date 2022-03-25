#include<iostream>
#include<cmath>
using namespace std;
void swap(int a,int b){
     int swap=a;
     a=b;
     b=swap;
}
void bubble(int * arr ,int len){
    for(int i=0;i<len-1;i++){
        for(int j=0;j<len-i-1;j++)
        swap(arr[j],arr[j+1]);
    }
}
int main(){
    int arr[5]={0};
    for (int i=0;i<sizeof(arr)/sizeof(0);i++){
        cin >> arr[i]; 
    }
    bubble(arr,sizeof(arr)/sizeof(0));
    for (int i=0;i<sizeof(arr)/sizeof(0);i++){
        cout << arr[i] << "> ";
    }
    return 0;
}