#include <algorithm>
#include <iostream>
using namespace std;
int main(){
    int a[10000];
    for (int i = 0; i < 10000; ++i){
        a[i] = 10000 - i;
        // console.log("🚀 ~ file: test.cc ~ line 8 ~ intmain ~ a[i]", a[i])
    }
    std::sort(a, a + 10000);
    // for (int i = 0; i < 10000; ++i){
    //     std::cout << a[i] << " ";
    // }
    return 0;
}
    // // console.log("🚀 ~ file: test.cc ~ line 15 ~ intmain ~ a", a)
