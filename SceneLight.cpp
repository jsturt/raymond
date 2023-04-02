#include "SceneLight.h"

SceneLight::SceneLight() {
    Vector3 origin;
    ColRGB lightCol;
    _pos = origin;
    _intensity = 1.0;
    _col = lightCol;
}

SceneLight::SceneLight(Vector3 pos, double intensity, ColRGB colour):_pos(pos),_intensity(intensity),_col(colour) {

}

SceneLight::SceneLight(const SceneLight &rhs) {
    _pos = rhs._pos;
    _intensity = rhs._intensity;
    _col = rhs._col;
}

void SceneLight::SetPos(Vector3 pos) {
    _pos = pos;
}

void SceneLight::SetIntensity(double intensity) {
    _intensity = intensity;
}

void SceneLight::SetColour(ColRGB col) {
    _col = col;
}
