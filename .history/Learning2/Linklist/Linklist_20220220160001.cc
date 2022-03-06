/*
 * @Date: 2022-02-20 14:08:00
 * @LastEditors: js
 * @LastEditTime: 2022-02-20 16:00:01
 * @FilePath: \code\Learning2\Linklist\Linklist.cc
 */
#include "Linklist.h"
#include <iostream>

int main(){
    Linklist linklist(5);
    linklist.reverse();
    linklist.print();
    return 0;
}