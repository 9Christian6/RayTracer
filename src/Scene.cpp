#include "Scene.hpp"
#include "Camera.hpp"
#include "Image.hpp"
#include "Intersection.hpp"
#include "OBJ_Loader.h"
#include "Ray.hpp"
#include "Triangle.hpp"
#include "Vector2.hpp"
#include <iostream>

namespace raytracer {
Scene::Scene(std::vector<Light> lights, ShapeSet shapes, Camera &cam)
    : _lights{lights}, _shapes{shapes}, _camera{cam} {};

void Scene::addShape(Shape *shape) { _shapes.addShape(shape); }

void Scene::addShapes(std::unique_ptr<objl::Loader> loader) {
  auto meshes = loader.get()->LoadedMeshes;
  for (auto mesh : meshes) {
    for (int i = 0; i < mesh.Indices.size(); i += 3) {
      auto idx0 = mesh.Indices[i];
      auto idx1 = mesh.Indices[i + 1];
      auto idx2 = mesh.Indices[i + 2];
      auto vert0 = mesh.Vertices[idx0];
      auto vert1 = mesh.Vertices[idx1];
      auto vert2 = mesh.Vertices[idx2];
      _shapes.addShape(new Triangle{vert0, vert1, vert2});
      std::cout << "T" << i / 3 << ": " << raytracer::Vector{vert0.Position}
                << ", " << raytracer::Vector{vert1.Position} << ", "
                << raytracer::Vector{vert2.Position} << "\n";
    }
  }
}

void Scene::addLight(Light &light) { _lights.push_back(light); }

void Scene::setCamera(const Vector &position, const Vector &upGuide,
                      const Vector &forward) {
  _camera.setPosition(position, upGuide, forward);
}

Color Scene::renderPixel(Ray &ray) const {
  auto hit = _shapes.intersect(ray);
  if (!hit)
    return {};
  if (auto hitColor = hit->color(visibleLights(*hit)))
    return *hitColor;
  return {};
}

void Scene::render(int width, int height) const {
  Image img{width, height};
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      auto ray = _camera.makeRay(width, height, {x, y});
      auto pixel = renderPixel(ray);
      img.plot(x, y, pixel);
      std::cout << "Line " << x  << "/" << width << ", pixel " << x * width + y << " rendered\n";
    }
  }
  img.write("../image/");
}

bool Scene::isVisible(const Vector &point, const Light &light) const {
  Ray lightRay{light.position(), point - light.position()};
  double tLength{(light.position() - point).length()};
  if (auto lightHit = _shapes.intersect(lightRay)) {
    return (tLength < lightHit->t() + 0.0001);
  }
  return true;
}

std::vector<Light> Scene::visibleLights(const Vector &point) const {
  std::vector<Light> visibleLights{};
  for (auto light : _lights) {
    if (isVisible(point, light))
      visibleLights.push_back(light);
  }
  return visibleLights;
}

std::vector<Light> Scene::visibleLights(const Intersection &hit) const {
  return visibleLights(hit.position());
}
} // namespace raytracer
