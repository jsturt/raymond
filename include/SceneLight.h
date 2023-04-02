#pragma once

#include "Vector3.h"
#include "ColRGB.h"
#include "Ray.h"


class SceneLight {
public:
    SceneLight();
    SceneLight(Vector3 pos, double intensity, ColRGB colour);
    SceneLight(const SceneLight& rhs);

    Vector3 GetPos(){return _pos;};
    double GetIntensity(){return _intensity;};
    ColRGB GetColour(){return _col;};

    void SetPos(Vector3 pos);
    void SetIntensity(double intensity);
    void SetColour(ColRGB col);

private:
    Vector3 _pos;
    double _intensity;
    ColRGB _col;
};