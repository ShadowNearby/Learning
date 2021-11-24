class Game{
public:
    int pos[3][3] = {0};
};
class judge : public Game{
private:
public:
    judge(){
        for (int i = 0; i < 3 ;++i){
            for (int j = 0; j < 3;++j){
                if (pos[i][j] == 0){
                    continue;
                }
            }
        }
    }
    ~judge();
};
