#include <iostream>
using namespace std;

void maxmin(int arr ,int size){
    auto max = *arr , min = *arr;
    for(int i = 0 ; i < size ; i++){
        if(max < *(arr + i)) max = *(arr + i);
        if(min > *(arr + i)) min = *(arr + i);
    }
    cout << max << " " << min << endl;
//}//你的代码




int main()
{
    int m, n;
    int arr_int[10000];
    double arr_double[10000];
    
    // 输入m和整型数组
    cin >> m;
    for(int i = 0; i < m; i++)
        cin >> arr_int[i];
    
    // 输入n和浮点型 数组
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arr_double[i];
    // 输出结果
    maxmin(arr_int, m);
    maxmin(arr_double, n);
    return 0;
}
