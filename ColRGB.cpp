#include "ColRGB.h"

ColRGB::ColRGB():_axes()
{
    _axes = {0.18f,0.18f,0.18f};
}


ColRGB::ColRGB(float a, float b, float c):_axes()
{   
    _axes = {a,b,c};
}

ColRGB::ColRGB(const ColRGB &rhs):_axes()
{
   _axes[0] = rhs._axes[0];
    _axes[1] = rhs._axes[1];
    _axes[2] = rhs._axes[2];
}

ColRGB::~ColRGB() = default;

void ColRGB::Set(float a, float b, float c)
{
   _axes[0] = a;
    _axes[1] = b;
    _axes[2] = c;
}

void ColRGB::SetElem(int index, float a)
{
   _axes[index] = a;
}

ColRGB ColRGB::operator+(const ColRGB &rhs)
{
   ColRGB temp;
    for (int i = 0; i < 3; ++i)
    {
       temp._axes[i] = _axes[i] + rhs._axes[i];
    }
    return temp;
}


ColRGB ColRGB::operator-(const ColRGB &rhs)
{
   ColRGB temp;
    for (int i = 0; i < 3; ++i)
    {
       temp._axes[i] = _axes[i] - rhs._axes[i];
    }
    return temp;
}

ColRGB ColRGB::operator=(const ColRGB &rhs) 
{
    if(this != &rhs)
    {
        _axes = rhs._axes;
    }
    return *this;
}

ColRGB ColRGB::operator*(float scale)
{
   ColRGB temp;
    for (int i = 0; i < 3; ++i) 
    {
        temp._axes[i] = _axes[i] * scale;
    }
    return temp;
}

ColRGB ColRGB::operator*(const ColRGB &rhs) 
{
    ColRGB temp;
    for (int i = 0; i < 3; ++i) 
    {
        temp._axes[i] = _axes[i] * rhs._axes[i];
    }
    return temp;
}

ColRGB ColRGB::operator/(float scale)
{
   ColRGB temp;
    for (int i = 0; i < 3; ++i)
    {
       temp._axes[i] = _axes[i] / scale;
    }
    return temp;
}

ColRGB ColRGB::operator/(const ColRGB &rhs) 
{
    ColRGB temp;
    for (int i = 0; i < 3; ++i) 
    {
        temp._axes[i] = _axes[i] / rhs._axes[i];
    }
    return temp;
}

void ColRGB::print()
{
   for (int i = 0; i < 3; ++i)
    {
       std::cout<<_axes[i]<<" ";
    }
    std::cout<<std::endl;
}