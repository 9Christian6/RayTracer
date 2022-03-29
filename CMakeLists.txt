cmake_minimum_required(VERSION 3.16)
project(RayTracer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PNGwriter 0.7.0)

add_subdirectory(src)
add_executable(RayTracer 
src/main.cpp
src/Ray.cpp
src/Vector.cpp
src/Plane.cpp
src/Sphere.cpp
src/Camera.cpp
src/Vector2.cpp
src/Image.cpp
include/Vector2.hpp
include/Camera.hpp
include/fEquals.hpp
include/Ray.hpp
include/Vector.hpp
include/Exception.hpp
include/Plane.hpp
include/Sphere.hpp
include/Hit.hpp
include/Image.hpp)

if(PNGwriter_FOUND)
  target_link_libraries(RayTracer PRIVATE PNGwriter::PNGwriter)
endif(PNGwriter_FOUND)


target_include_directories(RayTracer PRIVATE include)
target_include_directories(RayTracer PRIVATE 3rd-party)