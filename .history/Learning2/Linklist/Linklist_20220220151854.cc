/*
 * @Date: 2022-02-20 14:08:00
 * @LastEditors: js
 * @LastEditTime: 2022-02-20 15:18:54
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
    linklist.change(3, 100);
    linklist.reverse();
    linklist.print();
    std::cout << linklist.search(4) << " ";
    return 0;
}