project('RayTracer','cpp')

inc = include_directories('include')

src = ['ColRGB.cpp','main.cpp','Material.cpp','Ray.cpp','Scene.cpp','SceneLight.cpp','SceneObject.cpp','Timer.cpp','Vector3.cpp','Viewport.cpp']

EasyBMP_proj = subproject('EasyBMP')
EasyBMP_dep = EasyBMP_proj.get_variable('EasyBMP_dep')

sRGB_proj = subproject('sRGB')
sRGB_dep = sRGB_proj.get_variable('sRGB_dep')

executable('raymond', sources : src, dependencies : [EasyBMP_dep,sRGB_dep], include_directories : inc)

