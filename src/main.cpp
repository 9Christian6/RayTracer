#include "Camera.hpp"
#include "OBJ_Loader.h"
#include "Scene.hpp"
#include "Shapeset.hpp"
#include "Triangle.hpp"
#include "Vector.hpp"
#include <memory>

int main(int, char **) {
  // Vectors
  raytracer::Vector origin{0, 0, 0}, xVec{1, 0, 0}, yVec{0, 1, 0},
      zVec{0, 0, 1};

  // Camera
  raytracer::Camera camera{1.2 * zVec + 1.2 * yVec + 1.2 * xVec, origin, yVec, 45,
                           1};

  // Shapes
  raytracer::Plane xzPlane{origin, yVec};
  raytracer::Plane yzPlane{-xVec, xVec};
  auto shapes = raytracer::ShapeSet{{}};
  auto A = raytracer::Vector{-1, 1, 1};
  auto B = raytracer::Vector{1, 1, 1};
  auto C = raytracer::Vector{-1, 1, -1};
  auto D = raytracer::Vector{1, 1, -1};
  auto E = raytracer::Vector{-1, -1, 1};
  auto F = raytracer::Vector{1, -1, 1};
  auto G = raytracer::Vector{-1, -1, -1};
  auto H = raytracer::Vector{1, -1, -1};

  // Lights
  auto light = raytracer::Light{{0, 0, 0}};
  auto light1 = raytracer::Light{{3, 3, 3}};
  auto light2 = raytracer::Light{{3, 3, 10}};
  auto lights = {light2};

  // Loader
  auto loaderPointer = std::make_unique<objl::Loader>(objl::Loader{});
  loaderPointer->LoadFile(
      "/home/christian/Desktop/RayTracer/models/dice.obj");

  // Scene
  auto scene = raytracer::Scene{lights, shapes, camera};
  scene.addShapes(std::move(loaderPointer));
  auto tri0 = new raytracer::Triangle{A, B, D};
  auto tri1 = new raytracer::Triangle{A, C, D};
  auto tri2 = new raytracer::Triangle{B, D, H};
  auto tri3 = new raytracer::Triangle{B, F, H};
  auto tri4 = new raytracer::Triangle{A, C, G};
  auto tri5 = new raytracer::Triangle{A, E, G};
  auto tri6 = new raytracer::Triangle{C, D, G};
  auto tri7 = new raytracer::Triangle{D, G, H};
  auto tri8 = new raytracer::Triangle{E, F, G};
  auto tri9 = new raytracer::Triangle{F, G, H};
  auto tri10 = new raytracer::Triangle{A, B, E};
  auto tri11 = new raytracer::Triangle{B, E, F};
//  scene.addShape(tri0);
//  scene.addShape(tri1);
//  scene.addShape(tri2);
//  scene.addShape(tri3);
//  scene.addShape(tri4);
//  scene.addShape(tri5);
//  scene.addShape(tri6);
//  scene.addShape(tri7);
//  scene.addShape(tri8);
//  scene.addShape(tri9);
//  scene.addShape(tri10);
//  scene.addShape(tri11);
  scene.render(50, 50);
}
