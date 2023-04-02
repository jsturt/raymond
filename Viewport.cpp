#include "Viewport.h"

Vector3 Viewport::getPixel(int i, int j) 
{
    Vector3 pixel;                                                                              // Create unit vector in the screen direction
    Vector3 e1(1.0,0.0,0.0),e2(0.0,1.0,0.0),e3(0.0,0.0,1.0);          // Create unit vectors in the plane of the screen
    pixel = e1*(j - _x/2)*_d + e2*(i - _y/2)*_d + e3;                                           //  moving the pixel vector to the correct space and offsetting the viewport
   return pixel;
}

std::vector<Vector3> Viewport::latinHypercube(Vector3 pixel, int n, bool jitter)
{
    // latin hypercube sampling is an efficient way to sample a distribution, taking M rather than M^d samples over a space of dimension d.
    // vector of sub-pixel diagonal offset
    float delta = _d / n;
    Vector3 vDelta(delta,delta,0.0f);

    // set position to the centre of the bottom left sample 
    pixel = pixel - (vDelta * (n * 0.5f)) + (vDelta * 0.5f);
    std::vector<Vector3> samples;
    for (int i=0;i<n;++i) {samples.push_back(pixel + (vDelta * ((float) i)));}

    // Shuffle such that the sampling is representative of the distribution
    std::uniform_int_distribution gen(0,n-1);
    for (int i=0;i<n;++i) {std::swap(samples[i].Get()[1],samples[gen(_mt)].Get()[1]);}

    // Jitter sample position
    std::uniform_real_distribution genf(-delta / 2.0f, delta / 2.0f);
    if (jitter)
    {
        for (auto& elem : samples)
        {
            elem.SetElem(0, elem.GetElem(0) + genf(_mt));
            elem.SetElem(1, elem.GetElem(1) + genf(_mt));
        }
    }

    return samples;
}

void Viewport::setAA(int numAA, bool jitter)
{
    _numAA = numAA;
    _jitter = jitter;
}

void Viewport::render(Scene scene) 
{
    Timer timer;                                    // Setting up timer object to count the time for this scope
    // Setting up easyBMP methods
    BMP image;
    image.SetSize(_x,_y);
    image.SetBitDepth(_bitdepth);

    // RAY CASTING ------------------------------------------------------------------------

    Vector3 origin(0.0,0.0,0.0);                                                                // Vector for origin position of ray
    for (int i = 0; i < _y; ++i) 
    {
        for (int j = 0; j < _x; ++j) 
        {
            util::progressBar( (float) ((i * _x) + j ) / (_x * _y));
            ColRGB pixelData(0.0f,0.0f,0.0f);                                                   // Creating container for pixel colour
            Vector3 dir(getPixel(_y-i,j));                                                      // Getting pixel location, doing y-i to get into the top left corner
            std::vector<Vector3> sampleAA = latinHypercube(dir, _numAA, _jitter);               // Calculate where to direct AA samples
            for (auto& elem : sampleAA)
            {
                Ray ray(elem,origin);                                                           // Creating ray to pixel
                pixelData = pixelData + path(ray,scene.getObjects(),0);                         // Setting colour to sampled colour. 
                // pixelData = pixelData + sample(ray,scene.getObjects(),scene.getLights());       // Setting colour to sampled colour. 
                // pixelData = pixelData + sampleTest(ray,scene.getObjects(),scene.getLights());       // Setting colour to sampled colour. 
            }


            pixelData = pixelData / _numAA;                                            // Take average of found pixels to AA
            // basic placeholder clamping with gamma correction before display transform implementation.

            for (int i=0;i<3;i++) {pixelData.SetElem(i, SrgbTransform::linearToSrgb( std::min(pixelData.GetElem(i), 1.0f) ) * 255.0f );}
            image(j,i)->Red = (int) pixelData.Get()[0];                                         // Doing easyBMP work to load pixel data
            image(j,i)->Green = (int) pixelData.Get()[1];
            image(j,i)->Blue = (int) pixelData.Get()[2];
        }
    }
    image.SetBitDepth(32);
    image.WriteToFile("render.bmp");                                                            // Writing pixel data
}

void Viewport::setBitdepth(int bits) {
    _bitdepth = bits;
}

void Viewport::setBackground(const ColRGB& col) {
    _bg = col;
}

void Viewport::setMaxBounces(const unsigned int num) {
    _maxBounces = num;
}

ColRGB Viewport::sampleTest(Ray &ray, const std::map<std::string,std::shared_ptr<SceneObject>>& objects, const std::map<std::string,std::shared_ptr<SceneLight>>& lights) 
{
    // Check for intersections and sample colour if one occurs
    ColRGB sampled(_bg);                                    // Sample the background colour here!
    float dist = _farplane;                                 // Setting the check for nearest object at the far clipping plane

    for (const auto& obj:objects) 
    {                         // Loop over the objects in the scene
        float raydist= obj.second->intersection(ray);
        if (obj.second->isCollision(ray) && obj.second->intersection(ray)<dist)
        {
            dist=raydist;
            //sampled = obj.second->getCol();  // checking correct colour assignment
            // normals on range [-1,1]
            // colours on range [0,1]
            sampled.Set((obj.second->getNormal(ray).GetElem(1) * 0.5f) + 0.5f,(obj.second->getNormal(ray).GetElem(0) * 0.5f) + 0.5f,(obj.second->getNormal(ray).GetElem(2) * 0.5f) + 0.5f); // check normals
        }
    }
    return sampled * 255.0f;
}

ColRGB Viewport::path(Ray &ray, const std::map<std::string,std::shared_ptr<SceneObject>>& objects, unsigned int bounces) 
{
                                                            // Check for intersections and sample colour if one occurs
    ColRGB sampled(_bg);                                    // Sample the background colour here!
    ColRGB grey;
    if(bounces>_maxBounces) {return sampled;}              // Return if max depth reached.
    float dist = _farplane;                                 // Setting the check for nearest object at the far clipping plane
                                                            // Loop over the objects in the scene
    // Diffuse system block-out
    for (const auto& obj:objects) 
    {                         
        float raydist= obj.second->intersection(ray);
        if (obj.second->isCollision(ray) && obj.second->intersection(ray)<dist)
        {
            dist=raydist;
            Material mat = obj.second->getMat();
            // emissive materials
            if (mat.emission > 0.9f) {return mat.colour * mat.emission;}
            else
            {
                // pick random direction in hemisphere of the surface normal
                // Do this by uniformly generating point on a sphere, if dot with the normal < 0 then invert it via the normal!
                std::uniform_real_distribution gen(0.0d, M_PI);
                float theta = gen(_mt);
                float phi = gen(_mt) * 2.0f;

                Vector3 normal = obj.second->getNormal(ray);
                // generate pt on sphere
                Vector3 newDir( sin(theta) * cos(phi) , sin(theta) * sin(phi) , cos(theta) );

                if (newDir.Dot(normal) < 0)
                {
                    for (int i = 0; i < 3; ++i)
                    {
                        float sign = (float) util::sgn(normal.GetElem(i));
                        newDir.SetElem(i, newDir.GetElem(i) * sign);
                    }
                }
                // creating new ray with small offset to avoid floating point errors.
                Ray newRay(newDir, ray.getHit() + (newDir * 0.00001f));
                // calculate cos theta term for BRDF
                float cos_theta = newDir.Dot(normal);
                // calculate BRDF term. SHOULD BE DIV BY PI
                ColRGB reflectance = obj.second->getMat().colour; // / M_PI;
                // do recursion
                ColRGB incoming = path(newRay, objects, bounces+1);
                // evaluate trace             
                sampled = incoming + ( reflectance * cos_theta / (2 * M_PI) );
                // sampled = incoming + ( reflectance * cos_theta * 0.5f / (2 * M_PI) );
                // sampled = (mat.colour * mat.emission) + (incoming * reflectance * cos_theta / (2 * M_PI) );
            }
        }
    }
    return sampled;
}

ColRGB Viewport::sample(Ray &ray, const std::map<std::string,std::shared_ptr<SceneObject>>& objects, const std::map<std::string,std::shared_ptr<SceneLight>>& lights) {
    // TODO: Add in light colour consideration -> albedo
    // Check for intersections and sample colour if one occurs
    ColRGB sampled(_bg);                                    // Can set the background colour here!
    float dist = _farplane; // Setting the check for nearest object at +inf
    ColRGB one(1.0f,1.0f,1.0f);

    for (const auto& obj:objects) {                         // Loop over the objects in the scene
        float raydist= obj.second->intersection(ray);
        float diffuse=0;
        if (obj.second->isCollision(ray) && obj.second->intersection(ray)<dist){
            dist = raydist;

            // Diffuse reflection
            for (const auto& light:lights) {
                diffuse += obj.second->diffuseReflect(ray,*light.second) * light.second->GetIntensity() * 0.5f ; // TODO: add back in albedo (+ albedo)
            }
            sampled = (obj.second->getCol() + (one * diffuse)) * 255;
            // basic placeholder clamping before display transform implementation.
            for (int i=0;i<3;i++) {sampled.SetElem(i,std::min(sampled.GetElem(i),255.0f));}
            // std::array<int,3> RGB = sampled.hsv2rgb(sampled.rgb2hsv()[0],sampled.rgb2hsv()[1],diffuse*sampled.rgb2hsv()[2]); // Diffuse +1 to map into range of [0,1]
            // sampled.Set(RGB[0],RGB[1],RGB[2]);
        }
    }
    return sampled;
}

// ColRGB Viewport::sampleRef(Ray &ray, const std::map<std::string, std::shared_ptr<SceneObject>> &objects,const std::map<std::string, std::shared_ptr<SceneLight>> &lights) {
//     ColRGB sampled(0.0f,0.0f,0.0f);                                    // Can set the background colour here!
//     for (int i = 0; i < _maxBounces; ++i) {
//         float dist = std::numeric_limits<float>::infinity();  // Setting the check for nearest object at +inf
//         for (const auto &obj: objects) {                         // Loop over the objects in the scene

//             float raydist = obj.second->intersection(ray);
//             if (obj.second->isCollision(ray) && raydist < dist) {
//                 ColRGB col = obj.second->getCol();
//                 col.multiply(0.1);
//                 ray.getCol().addRGB(col);

//                 Vector3 hit = ray.getHit();                     // Setting up new ray
//                 Vector3 newDir = obj.second->reflect(ray);
//                 ray.setPos(hit);
//                 ray.setDir(newDir);

//                 sampled.setRGB(ray.getCol());
//             }
//         }
//     }
//     return sampled;
// }
