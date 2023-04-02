#include "Vector3.h"

Vector3::Vector3():_axes() {
    _axes = {1,1,1};
}


Vector3::Vector3(float a, float b, float c):_axes() {
    _axes = {a,b,c};
}

Vector3::Vector3(const Vector3 &rhs):_axes() {
    _axes[0] = rhs._axes[0];
    _axes[1] = rhs._axes[1];
    _axes[2] = rhs._axes[2];
}

float Vector3::Abs() {
    float sum = 0;
    for (int i = 0; i < 3; ++i) {
        sum += _axes[i]*_axes[i];
    }
    return sqrt(sum);
}

float Vector3::Dot(const Vector3 &rhs) {
    float sum = 0;
    for (int i = 0; i < 3; ++i) {
        sum += _axes[i]*rhs._axes[i];
    }
    return sum;
}

Vector3::~Vector3() = default;

void Vector3::Set(float a, float b, float c) {
    _axes[0] = a;
    _axes[1] = b;
    _axes[2] = c;
}

void Vector3::SetElem(int index, float a) {
    _axes[index] = a;
}

Vector3 Vector3::operator+(const Vector3 &rhs) {
    Vector3 temp;
    for (int i = 0; i < 3; ++i) {
        temp._axes[i] = _axes[i] + rhs._axes[i];
    }
    return temp;
}


Vector3 Vector3::operator-(const Vector3 &rhs) {
    Vector3 temp;
    for (int i = 0; i < 3; ++i) {
        temp._axes[i] = _axes[i] - rhs._axes[i];
    }
    return temp;
}

Vector3 Vector3::operator=(const Vector3 &rhs) {
    if(this != &rhs){
        _axes = rhs._axes;
    }
    return *this;
}

Vector3 Vector3::operator*(float scale) {
    Vector3 temp;
    for (int i = 0; i < 3; ++i) {
        temp._axes[i] = _axes[i]*scale;
    }
    return temp;
}

Vector3 Vector3::operator/(float scale) {
    Vector3 temp;
    for (int i = 0; i < 3; ++i) {
        temp._axes[i] = _axes[i]/scale;
    }
    return temp;
}

Vector3 Vector3::Cross(const Vector3 &rhs) {
    // Method to calculate the dot product between the current and another Vector3 object
    Vector3 temp;                   // Temporary Vector3 to hold calculated values
    int indices[5] = {1,2,3,1,2};   // Array to make finding correct indices easy
    for (int i = 0; i < 3; ++i) {
        temp._axes[i] =  _axes[indices[i+1]-1]*rhs._axes[indices[i+2]-1] - rhs._axes[indices[i+1]-1]*_axes[indices[i+2]-1];
    }
    return temp;
}

void Vector3::print() {
    for (int i = 0; i < 3; ++i) {
        std::cout<<_axes[i]<<" ";
    }
    std::cout<<std::endl;
}

