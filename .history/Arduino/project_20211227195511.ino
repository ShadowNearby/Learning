/*
 * @Date: 2021-12-22 13:23:31
 * @LastEditors: js
 * @LastEditTime: 2021-12-27 19:55:11
 * @FilePath: \code\Arduino\project.ino
 */
#include <Servo.h>
class ultrawave{
public: 
    int trig;
    int echo;
    double distance;
    //t for trig, e for echo
    ultrawave(const int t, const int e){
        trig = t;
        echo = e;
        pinMode(trig, OUTPUT);
        pinMode(echo, INPUT);
    }
    ~ultrawave();
    double measure();
    void print();
};
double ultrawave::measure(){
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    double time     = pulseIn(echo, HIGH);
           distance = (time * 0.034) / 2;
    return distance;
}
void ultrawave::print(){
    Serial.print("distance = ");
    Serial.print(distance);
    Serial.println(" cm ");
}
void shift(int times){
    for(int i = 0; i < times ; ++i){
        for (double i = 0; i <= 180; i++){
            myservo.write(i);
            delay(10);
        }
        //Serial.println("pause");
        for(double i = 180; i >= 0; i--){
            myservo.write(i);
            delay(10);
        }
        //Serial.println("pause");
    }
}
void setup(){
    ultrawave wave(2, 3);
    Servo myservo;
    myservo.attach(6);
    Serial.begin(9600);
}
void loop(){
    double distance;
    while(true){
        distance = wave.measure();
        wave.print();
        if(distance <= 5){
            shift(10);
        }
    }
}