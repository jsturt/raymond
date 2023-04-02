#pragma once

#define _USE_MATH_DEFINES

#include <array>
#include <algorithm>
#include <random>
#include <limits>
#include "cmath"
#include "Vector3.h"
#include "Scene.h"
#include "EasyBMP.h"
#include "Timer.h"
#include "Utility.h"
#include "SrgbTransform.hpp"

class Viewport 
{
public:
    Viewport(const int pixelX, const int pixelY, const double FOV):_x(pixelX), _y(pixelY), _d(2 * tan(M_PI*FOV/360.0)/pixelX),_bitdepth(8), _bg(0,0,0), _maxBounces(2), _mt(std::random_device()()) {};
    Vector3 getPixel(const int i, const int j);
    std::vector<Vector3> latinHypercube(Vector3 pixel, int n, bool jitter=true);
    void render(Scene scene);
    void setBitdepth(int bits);
    void setAA(int numAA, bool jitter);
    void setBackground(const ColRGB& col);
    void setMaxBounces(const unsigned int num);
    void setFarPlane(const float& distance) {_farplane=distance;}
    ColRGB path(Ray& ray, const std::map<std::string,std::shared_ptr<SceneObject>>& objects, unsigned int bounces);
    ColRGB sample(Ray& ray, const std::map<std::string,std::shared_ptr<SceneObject>>& objects, const std::map<std::string,std::shared_ptr<SceneLight>>& lights);
    ColRGB sampleTest(Ray& ray, const std::map<std::string,std::shared_ptr<SceneObject>>& objects, const std::map<std::string,std::shared_ptr<SceneLight>>& lights);
    ColRGB sampleRef(Ray& ray, const std::map<std::string,std::shared_ptr<SceneObject>>& objects, const std::map<std::string,std::shared_ptr<SceneLight>>& lights);

private:
    const int _x,_y;
    const float _d;
    float _farplane=100.0f;
    unsigned long _bitdepth;
    ColRGB _bg;
    unsigned int _maxBounces;        // 3 by default

    std::mt19937 _mt;
    bool _jitter;
    int _numAA=1;
};


/*
 _d is the offset between pixels
 the bottom left pixel is directly ahead of the camera
 the i'th+1 pixel is 1 unit away in z and _d in x
 the j'th+1 pixel is 1 unit away in z and _d in y
 offset the viewport by - pixelX / 2 and - pixelY / 2

 Normalise direction vectors
 */
