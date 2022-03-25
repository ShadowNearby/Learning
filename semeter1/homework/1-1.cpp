#include<iostream>
using namespace std;
int main(){
    int a,b,c,d,e;
    for(a=1;a<=9;a++){
        for(b=0;b<=9;b++){
            for(c=0;c<10;c++){
                for(d=1;d<=9;d++){
                    for(e=0;e<=9;e++){
                        if((a*1000+b*100+c*10+d)*e==a+b*10+c*100+d*1000&&a!=b&&a!=c&&a!=d&&a!=e&&b!=c&&b!=d&&b!=e&&c!=d&&c!=e&&d!=e){
                            cout << a <<" "<< b <<" "<< c <<" "<< d <<" "<< e <<endl;
                        }
                    }
                }
            }
        }
    }
    return 0;
}