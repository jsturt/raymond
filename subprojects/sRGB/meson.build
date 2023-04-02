project('sRGB','cpp')

inc = include_directories('include')

src = ['SrgbTransform.cpp']

sRGB = shared_library('sRGB', sources : src, include_directories : inc)

sRGB_dep = declare_dependency(include_directories : inc, link_with : sRGB)
