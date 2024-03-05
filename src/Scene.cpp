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
    for (int vertIdx = 0; vertIdx < mesh.Vertices.size() - 2; ++vertIdx) {
      auto tri = new Triangle{mesh.Vertices.at(vertIdx).Position,
                              mesh.Vertices.at(vertIdx + 1).Position,
                              mesh.Vertices.at(vertIdx + 2).Position};
      std::cout << tri->m_a << ", " << tri->m_b << ", " << tri->m_c << "\n";
      _shapes.addShape(tri);
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
    }
  }
  img.write("../image/");
}

bool Scene::isVisible(const Vector &point, const Light &light) const {
  Ray lightRay{light.position(), point - light.position()};
  double tLength{(light.position() - point).length()};
  if (auto lightHit = _shapes.intersect(lightRay)) {
    return (tLength < lightHit->t() + Ray::RAY_T_MIN);
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
  std::vector<Light> visibleLights{};
  auto point = hit.position();
  for (auto light : _lights) {
    auto plusNormal = point + hit.normal() * HIT_EPSILON;
    auto minNormal = point - hit.normal() * HIT_EPSILON;
    if ((plusNormal - light.position()).length() <
        (minNormal - light.position()).length())
      point = plusNormal;
    else
      point = minNormal;
    if (isVisible(point, light))
      visibleLights.push_back(light);
  }
  return visibleLights;
  // return visibleLights(hit.position() + hit.normal() * HIT_EPSILON);
}
} // namespace raytracer
