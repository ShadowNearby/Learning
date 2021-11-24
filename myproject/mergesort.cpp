#include<iostream>
#include<ctime>
long long n = 0,mergesortnum = 0,mergenum = 0;
void merge(int *arr, int l, int r,int *ans){
    ++mergenum;
    /*std::cout << "merge" << std::endl;
    std::cout << "ans : ";
    for (int i = 0; i < n; ++i){
        std::cout << ans[i] << " ";
    }
    std::cout << std::endl;*/
    int length = (r - l) / 2 + 1;
    int li = l, ri = l + length, anslen = l;
    while (li < l + length && ri < r + 1){
        if(arr[li] <= arr[ri]){
            ans[anslen++] = arr[li++];
        }
        else{
            ans[anslen++] = arr[ri++];
        }
    }
    while (li < l + length){
        ans[anslen++] = arr[li++];
    }
    while (ri < r + 1){
        ans[anslen++] = arr[ri++];
    }
    // std::cout << "ans : ";
    // for (int i = 0; i < n; ++i){
    //     std::cout << ans[i] << " ";
    // }
    // std::cout << std::endl;
}
void mergesort(int *arr,int l,int r,int *ans){
    ++mergesortnum;
    // std::cout << "mergesort" << std::endl;
    // std::cout << "arr : ";
    // for (int i = 0; i < n; ++i){
    //     std::cout << arr[i] << " ";
    // }
    // std::cout << std::endl;
    if(l >= r){
        return;
    }
    else if(l == r - 1){
        if(arr[l] > arr[r]){
        int temp = arr[l];
        arr[l] = arr[r];
        arr[r] = temp;
        }
    }
    else {
        mergesort(arr, l, (r + l) / 2 ,ans);
        mergesort(arr, (l + r) / 2 + 1, r ,ans);
    }
    merge(arr, l, r, ans);
    
    for (int i = l; i < r + 1; ++i){
        arr[i] = ans[i];
    }
}
int main(){
    while(n<2e8){
        long long time = clock();
        int *a = new int[n];
        // std::cout << "arr : ";
        for (int i = 0; i < n; ++i){
            a[i] = n - i;
            // std::cout << a[i] << " ";
        }
        // std::cout << std::endl;
        int *ans = new int[n];
        for (int i = 0; i < n; ++i){
            ans[i] = n - i;
        }
        mergesort(a, 0, n-1, ans);
        /* std::cout << "arr : ";
        for (int i = 0; i < n; ++i){
            std::cout << a[i] << " ";
        }
        std::cout << std::endl; */
        std::cout << n << " "<< mergenum << " " << mergesortnum << " " <<clock()-time << std::endl;
        
        delete[] a;
        delete[] ans;
        n += 1000000;
    }
    return 0;
}
/*std::cout << "arr : ";
    for (int i = 0; i < 20; ++i){
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "ans : ";
    for (int i = 0; i < 20; ++i){
        //std::cout << ans[i] << " ";
    }
    std::cout << std::endl;*/