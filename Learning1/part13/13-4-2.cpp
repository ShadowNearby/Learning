enum CPU_Rank
{
    P1 = 1,
    P2,
    P3,
    P4,
    P5,
    P6,
    P7
};
class CPU{
    private:
        enum CPU_Rank rank;
        int frequency;
        double voltage;
    public:
        CPU(enum CPU_Rank r,int f,double v){
            rank = r;
            frequency = f;
            voltage = v;
        }
        ~CPU(){
            cout << "This CPU has been deleted" << endl;
        }
        void run();
        void stop();
};