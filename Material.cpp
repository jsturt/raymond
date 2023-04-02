#include "Material.h"

Material::Material()
{
    // Simple grey material
    colour.Set(0.18f,0.18f,0.18f);
    roughness = 0.5f;
    emission = 0.0f;
    metalness = 0.0f;
}

Material::Material(const ColRGB& col, const float& rough, const float& emis, const float& metal): colour(col), roughness(rough), emission(emis), metalness(metal)
{

}

Material::Material(const Material& rhs)
{
    colour = rhs.colour;
    roughness = rhs.roughness;
    emission = rhs.emission;
    metalness = rhs.metalness;
}

Material::Material(const std::array<int,3>& RGB, const float& rough, const float& emis, const float& metal): roughness(rough), emission(emis), metalness(metal)
{
    colour.Set(RGB[0],RGB[1],RGB[2]);
}
