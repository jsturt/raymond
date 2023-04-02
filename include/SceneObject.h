#pragma once

#include "Vector3.h"
#include "SceneLight.h"
#include "Ray.h"
#include "Material.h"


class SceneObject 
{
public:
    // shape vector
    explicit SceneObject(const Vector3& pos, const Material& material):_position(pos),_rotation(0,0,0),_scale(1,1,1),_mat(material){};
    virtual ~SceneObject();

    Vector3 getPos(){return _position;}
    Vector3 getRot(){return _rotation;}
    Vector3 getScale(){return _scale;}
    ColRGB getCol() {return _mat.colour;}
    Material getMat() {return _mat;}
    void setPos(const Vector3 &rhs);
    void setRot(const Vector3 &rhs);
    void setScale(const Vector3 &rhs);

    Vector3 reflect(Ray &ray);
    float specularReflect(Ray &ray,SceneLight &light);
    float diffuseReflect(Ray &ray,SceneLight &light);

    virtual float intersection(Ray &ray) = 0;
    virtual bool isCollision(Ray &incident) = 0;
    virtual Vector3 getNormal(Ray &ray) = 0;

protected:
    Vector3 _ShapeVector;
    Vector3 _position;
    Vector3 _rotation;
    Vector3 _scale;
    Material _mat;
};


class Sphere: public SceneObject{
public:
    Sphere(const Vector3& pos, const Material& material, float radius): SceneObject(pos,material), _rad(radius){};
    float intersection(Ray &ray) override;
    bool isCollision(Ray &incident) override;

    Vector3 getNormal(Ray &ray) override;
private:
    float _rad;
};

class Plane: public SceneObject{
public:
    // Plane is specified by a normal vector plus a point in the plane.
    // We want the normal to be normalised
    Plane(const Vector3& position, const Material& material, const Vector3& normal): SceneObject(position,material), _normal(normal){};
    float intersection(Ray &ray) override;
    bool isCollision(Ray &incident) override;

    Vector3 getNormal(Ray &ray) override;
private:
    Vector3 _normal;
};
