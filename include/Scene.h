#pragma once

#include "Ray.h"
#include "Material.h"
#include "SceneLight.h"
#include "SceneObject.h"
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class Scene 
{
public:
    Scene();

    void ReadSceneFile(const std::string& filename);

    void AddSphere(const std::string& name, const Vector3& pos, const std::string& matName, float& rad);
    void AddLight(const std::string& name, const Vector3& pos, const ColRGB& col, float& intensity);
    void AddPlane(const std::string& name, const Vector3& pos, const std::string& matName, const Vector3& normal);
    void AddMaterial(const std::string& name, const ColRGB& colour, const float& roughness, const float& emission, const float& metalness);
    void AddMaterial(const Material& mat);
    void RemoveObject(const std::string& name);
    void RemoveLight(const std::string& name);

    std::map<std::string,std::shared_ptr<SceneObject>> getObjects(){return _objectList;};
    std::map<std::string,std::shared_ptr<SceneLight>> getLights(){return _lightList;};

private:
    std::map<std::string, std::shared_ptr<SceneObject>> _objectList;
    std::map<std::string, std::shared_ptr<SceneLight>> _lightList;
    std::map<std::string, std::shared_ptr<Material>> _materialList;
    // Using maps does slow down the execution slightly (+~1s), however the strength of named objects outweighs this
    // Being able to change a material by name after it is loaded from a file is a nice utility,
    // beats having to go through a vector by index and guess which object, light, material is which
};
