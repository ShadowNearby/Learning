class Location{
    public:
    double x = 0;
    double y = 0;
};
class Circle{
    private:
        double r = 0;
        Location o;
    public:
        Location getO(){
            return o;
        }
        double getR(){
            return r;
        }
        void setR(double radiu) {
            r = radiu;
        }
        void moveTo(double x,double y){
            o.x = x;
            o.y = y;
        }
        void print(){
            cout << "(" << o.x << " , " << o.y << ")  ";
            cout << "r = " << r;
        }
};