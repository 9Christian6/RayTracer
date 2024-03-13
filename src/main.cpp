#include "Camera.hpp"
#include "OBJ_Loader.h"
#include "Scene.hpp"
#include "Shapeset.hpp"
#include "Vector.hpp"
#include <chrono>
#include <memory>

using std::chrono::microseconds;

int main(int, char **) {
  // Vectors
  raytracer::Vector origin{0, 0, 0}, xVec{1, 0, 0}, yVec{0, 1, 0},
      zVec{0, 0, 1},
      // cameraPosition{2*xVec + -3*yVec + zVec};
      cameraPosition{1.5 * xVec + 6 * yVec + 1.5 * zVec};
  // cameraPosition{5.35889*xVec + -3.57579*yVec + 4.48831*zVec};

  // Camera
  raytracer::Camera camera{cameraPosition, origin, yVec, 10, 1};

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
  auto light2 = raytracer::Light{cameraPosition};
  auto lights = {light2};

  // Loader
  auto loaderPointer = std::make_unique<objl::Loader>(objl::Loader{});
  loaderPointer->LoadFile("/home/christian/Desktop/RayTracer/models/dice.obj");

  // Scene
  auto scene = raytracer::Scene{lights, shapes, camera};
  scene.addShapes(std::move(loaderPointer));
  // raytracer::Shape* tri0 = new raytracer::Triangle{A, B, D};
  // raytracer::Shape* tri1 = new raytracer::Triangle{A, C, D};
  // raytracer::Shape* tri2 = new raytracer::Triangle{B, D, H};
  // raytracer::Shape* tri3 = new raytracer::Triangle{B, F, H};
  // raytracer::Shape* tri4 = new raytracer::Triangle{A, C, G};
  // raytracer::Shape* tri5 = new raytracer::Triangle{A, E, G};
  // raytracer::Shape* tri6 = new raytracer::Triangle{C, D, G};
  // raytracer::Shape* tri7 = new raytracer::Triangle{D, G, H};
  // raytracer::Shape* tri8 = new raytracer::Triangle{E, F, G};
  // raytracer::Shape* tri9 = new raytracer::Triangle{F, G, H};
  // raytracer::Shape* tri10 = new raytracer::Triangle{A, B, E};
  // raytracer::Shape* tri11 = new raytracer::Triangle{B, E, F};
  // scene.addShape(tri0);
  // scene.addShape(tri1);
  // scene.addShape(tri2);
  // scene.addShape(tri3);
  // scene.addShape(tri4);
  // scene.addShape(tri5);
  // scene.addShape(tri6);
  // scene.addShape(tri7);
  // scene.addShape(tri8);
  // scene.addShape(tri9);
  // scene.addShape(tri10);
  // scene.addShape(tri11);
  scene.buildBVH();
  auto start = std::chrono::high_resolution_clock::now();
  scene.render(100, 100);
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start).count();
  std::cout << "The render took "<< duration << " seconds to finish" << "\n";
}
