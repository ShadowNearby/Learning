#pragma once

#include <iostream>
#include<vector>
using namespace std;
#include "CustomClass.h"
class Contend{
    virtual ostream& output(ostream &out){
        cout << "this type is not right" << endl;
    }
};
class IntContent : public Contend{
    private:
    int x;
    public:
    IntContent(int y) : x(y){}
    void output(ostream &out){
        out << y;
    }
    ~IntContent(){}
};
class StringContent : public Contend{
    private:
    string x;
    public:
    StringContent(string y) : x(y){}
    void output(ostream &out){
        out << y;
    }
    ~StringContent(){}
};
class VectorContent : public Contend{
    private:
    vector<Object> x;
    public:
};
class CustomClassContent : public Contend{
    private:
    CustomClass x;
    public:
    CustomClassContent(CustomClass y) : x(y){}
};
class Object : public Contend{
    private:
    Contend *p;
    public:
    Object(int y){
        p = new IntContent(y);
    }
    Object(string y){
        p = new StringContent(y);
    }
    Object(CustomClass y){
        p = new CustomClassContent(y);
    }
    ~Object(){
        p = NULL;
    }
    Object(){
        p = NULL;
    }
    Object operator=(const int y){
        p = new IntContent(y);
        return *this;
    }
    Object operator=(const string y){
        p = new StringContent(y);
        return *this;
    }
    Object operator=(const CustomClass y){
        p = new CustomClassContent(y);
        return *this;
    }
    Object operator=(const Object object){
        this->p = object.p;
    }
    friend ostream& operator<<(ostream &out,const Object &object){
        object.p->output(out);
        return out;
    }
    Object operator+=(int y){
        int t = *p;
        t += y;
        *p = t;
        return *this;
    }
    Object operator+=(string y){
        string t = *p;
        t += y;
        *p = t;
        return *this;
    }


};
