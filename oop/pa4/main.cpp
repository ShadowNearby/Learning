#include "MyList.h"
#include<iostream>
using namespace std;
int main(){
    // subtask 1
    mylist x;
    for(int i = 0; i < 5; i++)
        x.append(i);
    cout << x[0] << endl; // 0
    cout << x << endl; // [0, 1, 2, 3, 4]

    return 0;
}