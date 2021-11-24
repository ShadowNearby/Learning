#include "Vector.h"
Vector::Vector(int n){
    capacity = n;
    len = 0;
    array = new Node[n];
}
Vector::~Vector(){
    capacity = 0;
    len = 0;
    delete[] array;
    array = NULL;
}
int Vector::getlen(){
    return len;
}
Vector::Vector(const Vector &other){
    
    array = new Node[other.len];
    capacity = other.capacity;
    len = other.len;
    for (int i = 0; i < len; i++){
        *(array + i) = *(other.array + i);
    }
}
Vector::Vector(Vector && other){
    len = other.len;
    capacity = other.capacity;
    array = other.array;
    other.len = 0;
    other.capacity = 0;
    other.array = NULL;
}
Vector& Vector::operator=(const Vector & other){
    array = new Node[other.len];
    capacity = other.capacity;
    len = other.len;
    for (int i = 0; i < len; i++){
        *(array + i) = *(other.array + i);
    }
    return *this;
}
Vector& Vector::operator=(Vector && other){
    this->len = other.len;
    this->capacity = other.capacity;
    this->array = other.array;
    other.len = 0;
    other.capacity = 0;
    other.array = NULL;
    return *this;
}
Node& Vector::operator [] (int pos){
    return *(array + pos);
}
void Vector::append(int value){
    if(len == capacity){
        Node *tem = array;
        array = new Node[capacity+1];
        for (int i = 0; i < len; i++){
            *(array + i) = *(tem + i);
        }
        delete[] tem;
        tem = NULL;
        capacity += 1;
    }
    *(array + len++) = Node(value);
}
void Vector::insert(int pos, int value){
    if(len == capacity){
        Node *tem = array;
        array = new Node[capacity+1];
        for (int i = 0; i < len; i++){
            *(array + i) = *(tem + i);
        }
        delete[] tem;
        tem = NULL;
        capacity += 1;
    }
    for (int i = len; i > pos; i--){
        *(array + len) = *(array + len - 1);
    }
    *(array + pos) = Node(value);
}
void Vector::swap(int pos1, int pos2){
    Node temp = *(array + pos1);
    *(array + pos1) = *(array + pos2);
    *(array + pos2) = temp;
}
void Vector::dilatation(){
    Node *tem = array;
    array = new Node[capacity*2];
    for (int i = 0; i < len; i++){
        *(array + i) = *(tem + i);
    }
    delete[] tem;
    tem = NULL;
    capacity *= 2;
}