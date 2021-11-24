#include<iostream>
using namespace std;
const int maxsize=10;
int main(){
    int i,j,m,n;
    int mat[maxsize+1][maxsize];
    cin >> m >> n;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            cin >> mat[i][j];
        }
    }
    int temp[maxsize];
    for(j=0;j<n;j++){
            temp[j] = mat[m-1][j];
        }
    for(i=m-2;i>=0;i--){
        for(j=0;j<n;j++){
        mat[i+1][j]=mat[i][j];
        }
    }
    for(j=0;j<n;j++){
        mat[0][j]=temp[j];
    }
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            cout << mat[i][j] << ' ';
        }
        cout << endl;
    }
        return 0;
}