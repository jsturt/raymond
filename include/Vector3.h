#pragma once

#include <array>
#include <cmath>
#include <iostream>

class Vector3 {
public:
    Vector3();
    Vector3(float a, float b, float c);
    Vector3(const Vector3 &rhs);

    ~Vector3();

    void Set(float a, float b, float c);
    void SetElem(int index, float a);
    std::array<float,3>& Get(){return _axes;}
    float GetElem(int i){return _axes[i];}

    float Abs();
    float Dot(const Vector3 &rhs);
    Vector3 Cross(const Vector3 &rhs);

    Vector3 operator * (float scale);
    Vector3 operator / (float scale);
    Vector3 operator + (const Vector3 &rhs);
    Vector3 operator - (const Vector3 &rhs);
    Vector3 operator = (const Vector3 &rhs);

    void print();

private:
    std::array<float,3> _axes;
};