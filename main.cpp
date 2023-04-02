#include <iostream>
#include "Vector3.h"
#include "Scene.h"
#include "Viewport.h"

#include "ColRGB.h"

int main() 
{
    ColRGB midgrey;
    ColRGB black(0.0f,0.0f,0.0f);
    ColRGB darkgrey(0.05f,0.05f,0.05f);
    ColRGB lightBG(0.2f,0.2f,0.2f);
    ColRGB white(1.0f,1.0f,1.0f);
    ColRGB bbblue(0.25f,0.4f,0.45f);

    Scene scene;

    Viewport viewport(300,300,90.0);

    scene.ReadSceneFile("SceneFile.scene");

    scene.RemoveObject("ground2");          // Demonstrating removing objects created in the file
    //scene.RemoveObject("ground");          // Demonstrating removing objects created in the file

    viewport.setBackground(bbblue);
    viewport.setFarPlane(35.0f);
    viewport.setBitdepth(8);
    viewport.setAA(8, true);
    viewport.setMaxBounces(8);

    // scene.getObjects().find("sphere1")->second->getCol().print();

    viewport.render(scene);

    return 0;
}
