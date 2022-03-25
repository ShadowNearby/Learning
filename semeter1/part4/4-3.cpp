#include<iostream>
#include<iomanip>
using namespace std;
int main(){
    const double EPS = 1E-6;
    int i=1,n=1;
    double e,item;
    e=1;
    n=1;
    item=1;
    do{
        item*=i;
        e+=1.0/item;
        n++;
        i++;
    }while(1/item>=EPS);
    cout << fixed << setprecision(6) << e <<endl;
    return 0;
}