#include<iostream>
#include<ctime>
using namespace std;
int main(){
    cout << "幸运儿是： " ;
    srand(time(NULL));
    char *name[9]={"张一鸣","李一豪","梁世宇","东仕阳","闫景升","王天泽","王一飞","李芝","姜然"};
    int num = rand()%9;
    cout << name[num] <<endl;
    cout << clock();
    return 0;
}