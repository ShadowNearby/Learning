/*
 * @Date: 2022-02-20 14:08:00
 * @LastEditors: js
 * @LastEditTime: 2022-02-20 15:43:16
 * @FilePath: \code\Learning2\Linklist\Linklist.cc
 */
#include "Linklist.h"
#include <iostream>
int main(){
    Linklist linklist(1000);
    linklist.erase(2, 858);
    linklist.print();
    return 0;
}