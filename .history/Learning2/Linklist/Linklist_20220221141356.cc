/*
 * @Date: 2022-02-20 14:08:00
 * @LastEditors: js
 * @LastEditTime: 2022-02-21 14:13:56
 * @FilePath: \code\Learning2\Linklist\Linklist.cc
 */
#include "Linklist.h"
#include <iostream>

int main(){
    Linklist a(8), b(8);
    a.reverse();
    Linklist c = merge(a, b);
    c.print();
    return 0;
}