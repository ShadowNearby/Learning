#include<iostream>
#include<string>
using namespace std;
class zzh{
    public:
        static int zzhCount;
        double height;
        double weight;
        bool ishandsome;
        zzh(){
            zzhCount++;
        }
        void print(zzh * z);
        void getzzh(double , double ,bool);
    protected:
        string lover ;
};
typedef zzh zzh;
int zzh::zzhCount = 0;
void zzh::getzzh(double h, double w ,bool i){
    height = h;
    weight = w;
    ishandsome = i;
}
class inner_zzh:zzh{
    public:
    void getloverName(string);
};
void inner_zzh::getloverName(string name){
    lover = name;
}
void zzh::print(zzh *z){
    cout << "The zzh's height is " <<z->height << "cm" <<endl;
    cout << "The zzh's weight is " <<z->weight << "kg"<<endl;
    if(z->ishandsome == true) cout << "The zzh is handsome  "  <<endl;
    else cout << "The zzh is not handsome  "  <<endl;
    cout << "The number of zzh is " << z->zzhCount << endl;
}
int main(){
    zzh the_zzh;
    the_zzh.getzzh(178 , 60 , true);
    zzh *pointer = &the_zzh;
    the_zzh.print(pointer);
    return 0;
}