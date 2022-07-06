cmake_minimum_required(VERSION 3.16)
project(RayTracer VERSION 0.1.0 LANGUAGES CUDA CXX)

enable_language(CUDA)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(CMAKE_CXX_FLAGS "-Ofast")
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
  src/Intersection.cpp
  src/CUDAShape.cpp
  src/Shapeset.cpp
  src/Polygon.cpp
  src/Line2.cpp
  src/Ray2.cpp
  src/Color.cpp
  src/Light.cpp
  src/Scene.cpp
  src/Material.cpp
  src/BoundingBox.cpp
  src/CUDAScene.cpp
  src/CUDA.cu
  src/RenderKernel.cu
  include/Vector2.hpp
  include/Camera.hpp
  include/fEquals.hpp
  include/Ray.hpp
  include/Vector.hpp
  include/Exception.hpp
  include/Plane.hpp
  include/Sphere.hpp
  include/Image.hpp
  include/Intersection.hpp
  include/Shape.hpp
  include/CUDAShape.hpp
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
  include/CUDAScene.hpp
  include/CUDA.h
  include/RenderKernel.h
)

if(PNGwriter_FOUND)
  target_link_libraries(RayTracer PRIVATE PNGwriter::PNGwriter)
endif(PNGwriter_FOUND)

target_include_directories(RayTracer PRIVATE include)
target_include_directories(RayTracer PRIVATE 3rd-party)