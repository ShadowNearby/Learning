#include<iostream>
using namespace std;
struct Clock{
    int second;
    int minute;
    int hour;
    void settime(int, int, int);
    void increase();
    void showTime();
};
void Clock::settime(int h=0,int m=0,int s=0){
        hour = h;
        minute = m;
        second = s;
}
void Clock::increase(){
        second++;
        if(second==60){
            second = 0;
            minute++;
        }
        if(minute==60){
            minute = 0;
            hour++;
        }
        if(hour==24){
            hour=0;
        }
}
void Clock::showTime(){
        if(hour<10){
            cout << "0";
        }
        cout << hour <<":";
        if(minute<10){
            cout << "0";
        }
        cout << minute <<":";
        if(second<10){
            cout << "0";
        }
        cout << second << endl;
}
int main(){
    Clock clock;
    int s ,m ,h;
    cin >> h >> m >>s;
    clock.settime(h,m,s);
    clock.showTime();
    clock.increase();
    clock.showTime();
    cin >> h >> m >>s;
    clock.settime(h,m,s);
    clock.showTime();
    clock.increase();
    clock.showTime();
    return 0;
}
// 本关任务：编写程序模拟一个用于时间的电子时钟。该时钟以时、分和秒的形式记录时间。编写3个函数：

// setTime 函数用于设置时钟的时间，
// increase 函数模拟时间过去了1秒，
// showTime 显示当前时间，显示格式为HH:MM:SS。
// 注意时钟为24小时制。

// 编程要求
// 根据提示，在右侧编辑器补充代码。用户会输入六个整型数，分别代表第一次输入的时、分、秒和第二次输入的时、分、秒。输出每次输入的时间以及增加一秒后的时间

// 测试说明
// 平台会对你编写的代码进行测试：

// 测试输入：12 48 56 13 2 16
// 预期输出：
// 12:48:56
// 12:48:57
// 13:02:16
// 13:02:17