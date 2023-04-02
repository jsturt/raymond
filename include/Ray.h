#pragma once

#include "Vector3.h"

class Ray {
public:
    // constructor, copy constructor, get& set methods
    Ray(Vector3 direction, Vector3 position);       // Ray dir does not have to be normalised on input, is handled by the constructor
    //Ray(const Ray &rhs);
    ~Ray();

    Vector3 getDir(){return _dir;};
    Vector3 getPos(){return _pos;};
    Vector3 getHit();
    void setDir(Vector3& rhs);
    void setPos(Vector3& rhs);
    double getLambda(){return _lambda;}
    void setLambda(double lambda){_lambda = lambda;};

private:
    double _lambda;
    Vector3 _dir;
    Vector3 _pos;
};
