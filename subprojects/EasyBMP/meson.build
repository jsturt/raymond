project('EasyBMP','cpp')

inc = include_directories('include')

src = ['EasyBMP.cpp']

EasyBMP = shared_library('EasyBMP', sources: src,include_directories : inc)

EasyBMP_dep = declare_dependency(include_directories : inc, link_with : EasyBMP)
