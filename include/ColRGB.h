#pragma once

#include <array>
#include <cmath>
#include <iostream>

class ColRGB 
{
public:
    ColRGB();
    ColRGB(float a, float b, float c);
    ColRGB(const ColRGB &rhs);

    ~ColRGB();

    void Set(float a, float b, float c);
    void SetElem(int index, float a);
    std::array<float,3> Get(){return _axes;}
    float GetElem(int i){return _axes[i];}

    ColRGB operator * (float scale);
    ColRGB operator / (float scale);
    ColRGB operator * (const ColRGB &rhs);
    ColRGB operator / (const ColRGB &rhs);
    ColRGB operator + (const ColRGB &rhs);
    ColRGB operator - (const ColRGB &rhs);
    ColRGB operator = (const ColRGB &rhs);

    void print();

private:
    std::array<float,3> _axes;
};
