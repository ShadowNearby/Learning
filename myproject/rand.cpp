#include<iostream>
#include<ctime>
using namespace std;
int main(){
    cout << "���˶��ǣ� " ;
    srand(time(NULL));
    char *name[9]={"��һ��","��һ��","������","������","�ƾ���","������","��һ��","��֥","��Ȼ"};
    int num = rand()%9;
    cout << name[num] <<endl;
    cout << clock();
    return 0;
}