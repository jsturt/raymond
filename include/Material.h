#pragma once

#include "ColRGB.h"
#include <array>

struct Material
{
    Material();                     // Default constructor, produce a diffuse grey material
    Material(const ColRGB& col, const float& rough, const float& emis, const float& metal);
    Material(const Material& rhs);  // Copy constructor
    Material(const std::array<int,3>& RGB, const float& rough, const float& emis, const float& metal);

    ColRGB colour;                  // Base colour
    float roughness;                // Ratio between diffuse and specular light
    float emission;                 // Amount of emission
    float metalness;                // Parameter to control (dielectric - metal)ness 
};
