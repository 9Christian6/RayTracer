cmake_minimum_required(VERSION 3.16)
project(RayTracer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(src)
add_subdirectory(contrib/bvh)
add_executable(RayTracer 
src/main.cpp
src/Ray.cpp
src/Vector.cpp
src/Plane.cpp
src/Sphere.cpp
src/Camera.cpp
src/Vector2.cpp
src/Image.cpp
src/Intersection.cpp
src/Shapeset.cpp
src/Polygon.cpp
src/Line2.cpp
src/Ray2.cpp
src/Color.cpp
src/Light.cpp
src/Scene.cpp
src/Material.cpp
src/BoundingBox.cpp
src/Triangle.cpp
include/Vector2.hpp
include/Camera.hpp
include/fEquals.hpp
include/Ray.hpp
include/Vector.hpp
include/Exception.hpp
include/Plane.hpp
include/Sphere.hpp
include/Hit.hpp
include/Image.hpp
include/Intersection.hpp
include/Shape.hpp
include/Shapeset.hpp
include/Polygon.hpp
include/Line2.hpp
include/Ray2.hpp
include/SafeDivision.hpp
include/Color.hpp
include/Light.hpp
include/Scene.hpp
include/Material.hpp
include/BoundingBox.hpp
include/Triangle.hpp
include/OBJ_Loader.h
)

if(PNGwriter_FOUND)
  target_link_libraries(RayTracer PRIVATE PNGwriter::PNGwriter)
endif(PNGwriter_FOUND)
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(RayTracer PUBLIC OpenMP::OpenMP_CXX)
endif()
target_link_libraries(RayTracer PUBLIC bvh)

target_include_directories(RayTracer PRIVATE include)
target_include_directories(RayTracer PRIVATE 3rd-party)
