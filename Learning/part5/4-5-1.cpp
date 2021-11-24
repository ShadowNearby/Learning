#include<iostream>
using namespace std;
void swap(int &a,int &b){
    int temp=a;
    a=b;
    b=temp;

}
void sort(int arr[],int low,int high){
    int i=low,j=high;
    if(i>=j){
        return;
    }
    while(i<j){
        while(i<j&&arr[j]>=arr[low])
        j--;
        while(i<j&&arr[i]<=arr[low])
        i++;
        if(i<j){
            swap(arr[i],arr[j]);}
    }
    swap(arr[i],arr[low]);
    sort(arr,low,i-1);
    sort(arr,i+1,high);
}
int main(){
    int n=0;
    cin >> n;
    int arr[100];
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    sort(arr,0,n-1);
    for(int i=n-1;i>=0;i--){
        cout << arr[i] << " ";
    }
    return 0;
}
