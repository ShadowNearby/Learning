#include<iostream>
using namespace std;
int main(){
    double x1,y1,x2,y2,x3,y3;
    cin >> x1 >> y1 >>x2 >> y2 >> x3 >> y3;
    if((x1-x2)/(y1-y2)==(x2-x3)/(y2-y3)){
        cout << "yes" << endl;
    }
    else{
        cout << "no" << endl;
    }
    return 0;
}