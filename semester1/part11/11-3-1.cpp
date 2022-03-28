#include<iostream>
using namespace std;
struct vn{
    int s;
    int v;
    vn operator+(const vn &a){
        vn *ans = new vn;
        ans->s = a.s + this->s;
        ans->v = a.v + this->v;
        return *ans;
    }
    vn operator*(const vn &n){
        vn *ans = new vn;
        int a=this->s,b=this->v,c=n.s,d=n.v;
        ans->s = a*c-b*d;
        ans->v = b*c+a*d;
        return *ans;
    }
    vn operator+=(const vn &a){
        *this = *this + a;
        return *this;
    }
    vn operator*=(const vn &a){
        *this = *this * a;
        return *this;
    }
    void in(){
        int ss, vv;
        cin >> ss >>vv;
        s = ss;
        v = vv;
    }
    void out(){
        cout << this->s;
        if(this->v > 0){
            cout << "+" << this->v << "i" <<endl;
        }
        else if(v<0){
            cout << "-" << -this->v <<"i" <<endl;
        }
    }
    friend void out(const vn &a){
        if(a.s != 0){
            cout << a.s;
            if(a.v > 0){
                cout << "+" << a.v << "i" <<endl;
            }
            else if(a.v < 0){
                cout << "-" << -a.v <<"i" <<endl;
            }
            else{
            cout << endl;
        }
        }
        else{
            if(a.v > 0){
                cout << a.v << "i" <<endl;
            }
            else if(a.v < 0){
                cout << a.v <<"i" <<endl;
            }
            else{
                cout << 0 << endl;
            }
        }
        
    }
};

int main(){
    vn num1,num2;
    num1.in();
    num2.in();
    cout << "x = ";
    out(num1);
    cout << "y = ";
    out(num2);
    num1 += num2;
    cout << "x += y; x = ";
    out(num1);
    num2 *= num1;
    cout << "y *= x; y = ";
    out(num2);
    cout << "x + y = ";
    out(num1 + num2);
    cout << "y * x = ";
    out(num1 * num2);
    cout << "x = ";
    out(num1);
    cout << "y = ";
    out(num2);
    return 0;
}
// 本关任务：用结构体表示一个复数，编写实现复数的加法、乘法、和输出的函数。

// 编程要求
// 根据提示，在右侧编辑器补充代码，输入四个整型数a, b, c, d，分别代表复数x = a + bi 和y = c + di。然后依次计算输出：
// x = ?
// y = ?
// x += y; x = ?
// y *= x; y = ?
// x + y = ?
// y * x = ?
// x = ?
// y = ?
// 其中？为一个复数

// 测试说明
// 平台会对你编写的代码进行测试：

// 测试输入：1 2 3 4
// 输入说明：表示1+2i和3+4i两个复数
// 预期输出：
// x = 1+2i
// y = 3+4i
// x += y; x = 4+6i
// y *= x; y = -12+34i
// x + y = -8+40i
// y * x = -252+64i
// x = 4+6i
// y = -12+34i 
// 注意：不要输出类似3+0i的情况