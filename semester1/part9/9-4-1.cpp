#include<iostream>
using namespace std;
int search(int arr[],int n,int key){
    int i=0;
    for(i=0;i<n;i++){
        if(*(arr+i)==key) {
            return i;
            break;
            }
    }
    return -1;
}
int main(){
    int arr[20],n,key;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    cin >> key;
    int m=search(arr,n,key);
    if(m!=-1)cout << m << endl;
    else cout << "Not Found" << endl;
    return 0;
}