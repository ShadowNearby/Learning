#include<cstring>
class longlong{
    private:
        int len;
        char *num ;

    public:
    ~longlong(){
        delete num;
    }
    longlong(char *a){
        len = strlen(a);
        *num = new char[len * 2];
        for (int i = 0; i < len;i++){
            num[i] = a[i];
        }
    }
    longlong(){
        len = 0;
        *num = new char[4];
    }
    void print(){
        for (int i = 0; i < len;i++){
            cout << num[i];
        }
    }
    longlong operator=(char *a){
        len = strlen(a);
        *num = new char[len * 2];
        for (int i = 0; i < len;i++){
            num[i] = a[i];
        }
        return this;
    }
    longlong operator=(longlong a){
        this->len = a.len;
        this->num = a.num;
        for (int i = 0; i < len;i++){
            this->num[i] = a.num[i];
        }
        return this;
    }
};