/*
 * @Date: 2022-02-20 14:08:00
 * @LastEditors: js
 * @LastEditTime: 2022-02-20 15:37:18
 * @FilePath: \code\Learning2\Linklist\Linklist.cc
 */
#include "Linklist.h"
#include <iostream>
int main(){
    Linklist linklist(5);
    for (int i = 0; i < 5; ++i){
        linklist.insert(i, i);
        linklist.print();
        linklist.del(i);
    }
    linklist.erase(2, 4);
    linklist.print();
    return 0;
}