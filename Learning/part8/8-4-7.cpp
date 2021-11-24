#include<iostream>
using namespace std;
void swap(int arr[],int a,int b){\
    int temp = arr[a];
    arr[a] = arr[b];
    arr [b] = temp;
}
void Insert_Sort(int A[],int n)
 {
    if(n>0)
    {
        if(n>1){Insert_Sort(A,n-1);
        for(int i = n-1; i > 0 ;i--){
            if(A[i] < A[i-1]) swap(A , i , i-1);
        } //递归将前面n-1个元素排序好
        // 你的代码，把第n个元素插入到前面n-1个元素中
        }
    }
    }


int main()
{
    int n,num[1000];
    cin >> n ;
    for(int i = 0 ;i < n ;i++){
        cin >> num[i];
    }
    // 你的代码
    Insert_Sort(num,n);
    for(int i = 0;i < n ;i++){
        cout << num[i] <<" ";
    }
	return 0;
}
