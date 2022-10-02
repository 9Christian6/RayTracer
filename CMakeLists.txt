cmake_minimum_required(VERSION 3.16)
project(RayTracer VERSION 0.1.0 LANGUAGES CUDA CXX)

enable_language(CUDA)

# if(NOT CMAKE_BUILD_TYPE)
# set(CMAKE_BUILD_TYPE Release)
# endif()
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PNGwriter 0.7.0)

add_subdirectory(src)
add_executable(RayTracer
  src/main.cpp
  src/CUDAShape.cpp
  src/CUDAScene.cpp
  src/Vector3.cpp
  include/Vector3.hpp
  include/fEquals.hpp
  include/Exception.hpp
  include/CUDAShape.hpp
  include/SafeDivision.hpp
  include/CUDAScene.hpp
)

target_compile_options(RayTracer PRIVATE "-Wpedantic")
target_compile_options(RayTracer PRIVATE "-Wall")
target_compile_options(RayTracer PRIVATE "-Wextra")

if(PNGwriter_FOUND)
  target_link_libraries(RayTracer PRIVATE PNGwriter::PNGwriter)
endif(PNGwriter_FOUND)

target_include_directories(RayTracer PRIVATE include)
target_include_directories(RayTracer PRIVATE 3rd-party)