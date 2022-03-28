cmake_minimum_required(VERSION 3.16)
project(RayTracer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(3rd-party/eigen-3.4.0)
add_subdirectory(src)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake/Modules)
find_package(GMP REQUIRED)
INCLUDE_DIRECTORIES(
    "${GMP_INCLUDES}"
    "${CMAKE_SOURCE_DIR}/src"
)
 
add_executable(RayTracer 
src/main.cpp
src/Ray.cpp
src/Vector.cpp
src/Plane.cpp
src/Sphere.cpp
include/fEquals.hpp
include/Ray.hpp
include/Vector.hpp
include/Exception.hpp
include/Plane.hpp
include/Sphere.hpp
include/Hit.hpp)

target_link_libraries(RayTracer PRIVATE gmp gmpxx)
target_link_libraries(RayTracer PRIVATE eigen)
target_include_directories(RayTracer PRIVATE include)
target_include_directories(RayTracer PRIVATE 3rd-party)