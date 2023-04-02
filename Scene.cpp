#include "Scene.h"

Scene::Scene() {}

void Scene::AddSphere(const std::string& name, const Vector3& pos, const std::string& matName, float& rad) 
{
    std::shared_ptr<Sphere> object = std::make_shared<Sphere>(pos,*_materialList.find(matName)->second,rad);
    _objectList[name] = (object);
}

void Scene::AddLight(const std::string& name, const Vector3& pos, const ColRGB& col, float& intensity) 
{
    std::shared_ptr<SceneLight> object = std::make_shared<SceneLight>(pos,intensity,col);
    _lightList[name] = object;
}

void Scene::AddPlane(const std::string& name, const Vector3& pos, const std::string& matName, const Vector3& normal) 
{
    std::shared_ptr<Plane> plane = std::make_shared<Plane>(pos, *_materialList.find(matName)->second, normal);
    _objectList[name] = plane;
}

void Scene::AddMaterial(const std::string& name, const ColRGB& colour, const float& roughness, const float& emission, const float& metalness) 
{
    std::shared_ptr<Material> mat = std::make_shared<Material>(colour,roughness,emission,metalness);
    _materialList[name] = mat;
}

void Scene::RemoveObject(const std::string& name) 
{
    _objectList.erase(name);
}

void Scene::RemoveLight(const std::string& name) 
{
    _lightList.erase(name);
}

void Scene::ReadSceneFile(const std::string& filename)
{
    std::map<std::string,int> headers               // Map to allow for simple switch statement
    {
        std::make_pair("MAT", 0),
        std::make_pair("SPH", 1),
        std::make_pair("PLA", 2),
        std::make_pair("LHT", 3)
    };

    std::vector<std::string> filecontents;          // Vector to store contents of the file
    std::vector<std::string>::iterator it;          // Iterator for vector
    std::ifstream sceneFile(filename);              // Load file
    std::string line;                               // String for lines in the file

    if (sceneFile.is_open())
    {
        // Loop over lines in the file
        while(std::getline(sceneFile,line))
        {
            // Must strip CR characters from EOL for scene files generated on Windows to not throw errors on Linux
            line.erase(line.find_last_of("\r"));
            filecontents.push_back(line);
        }
        sceneFile.close();
    }
    else
    {
        std::cout << "unable to open file" << std::endl;
    }

    for (it = filecontents.begin(); it !=filecontents.end(); it++) 
    {
        line=*it;

        if (line.empty()){continue;}           // Skip to next line if line is empty
        if (line[0] == 35 ){continue;}             // Skip to next line if we find a comment (ASCII character 35)

        // Interpreting data //

        // Temporary material variables
        std::string name;
        ColRGB col;
        float roughness;
        float emission;
        float metalness;

        // Temporary object variables, can reuse RGB, floats from material to save an assignment
        Vector3 posvec;
        Vector3 norm;
        float radius = 1;
        std::string matName;

        switch (headers.find(line)->second)
        {
            case 0:
                std::advance(it,1);                                 // Advancing to next line
                name = (*it).substr(it->find(" ")+1);               // Using substrings and iterators to find the name variable

                std::advance(it,1);
                for (int i=0;i<3;i++) 
                {
                    unsigned long long pos = it->find(" ")+1;
                    col.SetElem(i, std::stof((*it).substr(pos)));
                    it->erase(0,pos);
                }

                std::advance(it,1);
                roughness = std::stof((*it).substr(it->find(" ")+1));

                std::advance(it,1);
                emission = std::stof((*it).substr(it->find(" ")+1));

                std::advance(it,1);
                metalness = std::stof((*it).substr(it->find(" ")+1));

                AddMaterial(name,col,roughness,emission,metalness);
                std::cout<<"Loading material : "<<name<<"\n";
                break;

            case 1:
                std::advance(it,1);
                name = (*it).substr(it->find(" ")+1);

                std::advance(it,1);
                for (int i=0;i<3;i++)
                {
                    unsigned long long pos = it->find(" ")+1;
                    posvec.SetElem(i,std::stof((*it).substr(pos)));
                    it->erase(0,pos);
                }

                std::advance(it,1);
                radius = std::stof((*it).substr(it->find(" ")+1));

                std::advance(it,1);
                matName = (*it).substr(it->find(" ")+1);

                if (_materialList.count(matName)==0)
                {
                    std::cout<<"Material "<<matName<<" not found."<<"\n";
                    std::cerr<<"Cant load sphere "<<name<<"\n";
                    break;
                }

                std::cout<<"Loading sphere : "<<name<<"\n";
                AddSphere(name,posvec,matName,radius);
                break;

            case 2:
                std::advance(it,1);
                name = (*it).substr(it->find(" ")+1);

                std::advance(it,1);
                for (int i=0;i<3;i++)
                {
                    unsigned long long pos = it->find(" ")+1;
                    posvec.SetElem(i,std::stof((*it).substr(pos)));
                    it->erase(0,pos);
                }

                // std::advance(it,1);
                // for (int i=0;i<3;i++) 
                // {
                //     unsigned long long pos = it->find(" ")+1;
                //     RGB[i] = std::stoi((*it).substr(pos));
                //     it->erase(0,pos);
                // }

                std::advance(it,1);
                for (int i=0;i<3;i++) 
                {
                    unsigned long long pos = it->find(" ")+1;
                    norm.SetElem(i,std::stof((*it).substr(pos)));
                    it->erase(0,pos);
                }

                std::advance(it,1);
                matName = (*it).substr(it->find(" ")+1);

                std::cout<<"Loading plane : "<<name<<"\n";

                if (_materialList.count(matName)==0)
                {
                    std::cout<<"Material "<<matName<<" not found."<<"\n";
                    std::cerr<<"Cant load plane "<<name<<"\n";
                    break;
                }

                AddPlane(name,posvec,matName,norm);
                break;

            case 3:
                std::advance(it,1);
                name = (*it).substr(it->find(" ")+1);

                std::advance(it,1);
                for (int i=0;i<3;i++) 
                {
                    unsigned long long pos = it->find(" ")+1;
                    posvec.SetElem(i,std::stof((*it).substr(pos)));
                    it->erase(0,pos);
                }

                std::advance(it,1);
                emission = std::stof((*it).substr(it->find(" ")+1));

                std::advance(it,1);
                for (int i=0;i<3;i++) 
                {
                    unsigned long long pos = it->find(" ")+1;
                    col.SetElem(i, std::stof((*it).substr(pos)));
                    it->erase(0,pos);
                }

                std::cout<<"Loading light : "<<name<<"\n";
                AddLight(name,posvec,col,emission);
                break;

            default:
                std::cout<<"Unrecognised input : " << line << "\n";
                break;
        }
    }
}