#include<iostream>
using namespace std;
class Clock{
private:
    int second;
    int minute;
    int hour;
public:
    void settime(const int, const int, const int);
    void increase();
    void decrease();
    void showTime();
    friend Clock &change(int);
    void operator+=(const int);
    void operator-=(const int);
    void operator++();
    void operator--();
    void operator=(Clock &clock);
    int operator-(const Clock&);
    friend ostream &operator<<(ostream &os, Clock &clock);
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
void Clock::decrease(){
        second--;
        if(second==-1){
            second = 0;
            minute--;
        }
        if(minute==-1){
            minute = 0;
            hour--;
        }
        if(hour==-1){
            hour=0;
        }
}
void Clock::showTime(){
    int hour = this->hour;
    int minute = this->minute;
    int second = this->second;
    if (hour < 10)
    {
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
Clock &change(int i){
    static Clock ans;
    ans.hour = i / 3600;
    i %= 3600;
    ans.minute = i / 60;
    ans.second = i % 60;
    return ans;
}
void Clock::operator+=(const int i){
    for (int j = 0; j < i; ++j){
        increase();
    }
}
void Clock::operator-=(const int i){
    for (int j = 0; j < i; ++j){
        decrease();
    }
}
void Clock::operator=(Clock &clock){
    this->hour = clock.hour;
    this->minute = clock.minute;
    this->second = clock.second;
}
void Clock::operator++(){
    increase();
}
void Clock::operator--(){
    decrease();
}
int Clock::operator-(const Clock &minus){
    int ans;
    ans = (hour - minus.hour) * 3600 + (minute - minus.minute) * 60 + (second - minus.second);
    if(ans < 0){
        return -ans;
    }
    else
        return ans;
}
ostream &operator<<(ostream &os, Clock &clock){
    clock.showTime();
    return os;
}
int main(){
    Clock clock, temp;
    clock.settime(20, 18, 16);
    temp = clock;
    cout << clock;
    clock += 5;
    clock.showTime();
    temp.showTime();
    ++clock;
    clock.showTime();
    --clock;
    clock.showTime();
    int seconds = clock - temp;
    cout << seconds << endl;
    temp = change(seconds);
    cout << temp;

    return 0;
}