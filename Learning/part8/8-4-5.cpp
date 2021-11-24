#include<iostream>
using namespace std;
int maxnum(int arr[],int size){
    if(size<1){
        cout <<"wrong"<< endl;
        return 0;
    }
    if(size==1){
        return arr[0]; 
    }
    int mid=size/2;
    return maxnum(arr,mid) > maxnum(&(arr[mid]),size-mid) ? maxnum(arr,mid) : maxnum(&(arr[mid]),size-mid);
}
int main(){
    int arr[5]={1,2,3,6,5};
    for(int i=0;i<5;i++){
        //cin >> arr[i];
    }
    cout << maxnum(arr,5) << endl;
    return 0;
}