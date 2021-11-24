#include <iostream>
class Point{
private:
    int x, y, z;
public:
    Point &operator-(){
        x = -x;
        y = -y;
        z = -z;
        return *this;
    }
    friend std::istream &operator>>(std::istream &is, Point &p){
       is >> p.x >> p.y >> p.z;
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Point &p){
        os << p.x << " " << p.y << " " << p.z << std::endl;
        return os;
    }
};
int main(){
    Point p1, p2;
    std::cin >> p1;
    p2 = -p1;
    std::cout << p2;
}