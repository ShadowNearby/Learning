#include<iostream>
using namespace std;
int main(){
    int m,n;
    cin >> m >> n;
    int arr[10][10],max[10],min[10];
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin >> arr[i][j];
    }}
    for(int j=0;j<n;j++){
        min[j]=arr[0][j];
        for(int i=0;i<m;i++){
            if (arr[i][j]<min[j]){
                min[j]=arr[i][j];
            }
        }
    }
    for(int i=0;i<m;i++){
        max[i]=arr[i][0];
        for(int j=0;j<n;j++){
            if (arr[i][j]>max[i]){
                max[i]=arr[i][j];
                
            }   
        }
    }
    int flag=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(min[j]==max[i]){
            cout << "mat["<<i << "]["<< j << "]=" <<  arr[i][j] << endl;
            flag++;
            }
    }
    }
     
    if (flag==0) cout << "Not Found" << endl;
    return 0;
}