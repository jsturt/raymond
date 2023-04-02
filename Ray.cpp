#include "Ray.h"

Ray::Ray(Vector3 direction, Vector3 position):_dir(direction),_pos(position){
    _dir = _dir / sqrt(_dir.Dot(_dir));         // Normalise rays on construction
}

Ray::~Ray() {}

Vector3 Ray::getHit() {
    return (_dir * _lambda) + _pos;
}

void Ray::setDir(Vector3 &rhs) {
    _dir = rhs / sqrt(rhs.Dot(rhs));
}

void Ray::setPos(Vector3 &rhs) {
    _pos = rhs;
}
