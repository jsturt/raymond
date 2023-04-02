#include "SceneObject.h"

SceneObject::~SceneObject() = default;

Vector3 SceneObject::reflect(Ray &ray){
    return ray.getDir() - getNormal(ray)*2*(ray.getDir().Dot(getNormal(ray)));
}

float SceneObject::diffuseReflect(Ray &ray,SceneLight &light) {
    Vector3 dir = light.GetPos() - ray.getHit();
    Ray ray2Light(dir,ray.getHit());
    return std::max(0.0f,ray2Light.getDir().Dot(getNormal(ray)));
}

float SceneObject::specularReflect(Ray &ray,SceneLight &light) {
    Vector3 dir = light.GetPos() - ray.getHit();
    dir = dir / dir.Abs();
    return std::max(0.0f,reflect(ray).Dot(dir));
}

bool Sphere::isCollision(Ray &incident) {
    Vector3 vMin = _position - incident.getPos();
    vMin = incident.getDir() * vMin.Dot(incident.getDir()) + incident.getPos() - _position;
    return vMin.Abs()<_rad;
}

float Sphere::intersection(Ray &ray) {
    // Need to solve the quadratic of the intersection of the ray with the sphere.
    float lambda,lambda2,a,b,c,det;
    Vector3 dir(ray.getDir()),pos(ray.getPos()),bbrac;
    a = dir.Dot(dir);
    bbrac = pos - _position;
    b = dir.Dot(pos - _position)*2.0f;
    c = bbrac.Dot(bbrac)- (_rad*_rad);

    det = sqrt((b*b)-4*a*c);
    lambda = 0.5f*(-b+det)/a;
    lambda2 = 0.5f*(-b-det)/a;
    if (lambda<=lambda2){
        ray.setLambda(lambda);
        return lambda;
    }
    else{
        ray.setLambda(lambda2);
        return lambda2;
    }
}


Vector3 Sphere::getNormal(Ray &ray) {
    Vector3 point = ray.getHit();       // Finding point on sphere
    Vector3 normal = point - _position;
    normal = normal / normal.Abs();     // Calculating normal
    return normal;
}

float Plane::intersection(Ray &ray) {
    Vector3 numerator = (_position - ray.getPos());
    float lambda = numerator.Dot(_normal);
    float denominator = ray.getDir().Dot(_normal);
    ray.setLambda(lambda/denominator);
    return lambda/denominator;
}

bool Plane::isCollision(Ray &incident) {
    if (incident.getDir().Dot(_normal) > 9e-9){return true;}
    else{return false;}
}

Vector3 Plane::getNormal(Ray &ray) {
    return _normal*-1;      //TODO: I've added a -1 here since the plane has to have inverted normals in order to not have the black line
}






























