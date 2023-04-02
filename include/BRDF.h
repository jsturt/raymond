#pragma once

#include "ColRGB.h"-
#include "Vector3.h"

class Lambertian
{
public:
	Lambertian();
	ColRGB reflectance();
	Vector3 reflectDirection();

private:

};

class GGX
{
public:
	GGX();
	ColRGB reflectance();
	Vector3 reflectDirection();

private:

}

class BRDF
{
public:
	BRDF(Lam);
	ColRGB reflectance();
	Vector3 reflectDirection();

private:
	Lambertian _lam;
	GGX _ggx;

};
