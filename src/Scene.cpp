#include "Scene.hpp"
#include "Camera.hpp"
#include "Image.hpp"
#include "Intersection.hpp"
#include "OBJ_Loader.h"
#include "Ray.hpp"
#include "Triangle.hpp"
#include "Vector2.hpp"
#include <string>

namespace raytracer {
Scene::Scene(std::vector<Light> lights, ShapeSet shapes, Camera &cam)
    : m_lights{lights}, m_shapes{shapes}, m_camera{cam} {
  m_shapes.buildBVH();
};

void Scene::buildBVH() { m_shapes.buildBVH(); }

void Scene::addShape(Shape *shape) { m_shapes.addShape(shape); }

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
      auto tri = new Triangle{vert0, vert1, vert2};
      tri->SetMaterial(mesh.MeshMaterial);
      m_shapes.addShape(tri);
    }
  }
}

void Scene::addLight(Light &light) { m_lights.push_back(light); }

void Scene::setCamera(const Vector &position, const Vector &upGuide,
                      const Vector &forward) {
  m_camera.setPosition(position, upGuide, forward);
}

Color Scene::renderPixel(Ray &ray) const {
  auto hit = m_shapes.intersect(ray);
  if (!hit)
    return {};
  if (auto hitColor = hit->color(visibleLights(*hit)))
    return *hitColor;
  return {};
}

void Scene::render(int width, int height) const {
  Image img{width, height};
#pragma omp parallel for
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      auto ray = m_camera.makeRay(width, height, {x, y});
      auto pixel = renderPixel(ray);
      img.plot(x, y, pixel);
    }
  } // namespace raytracer
  img.write("../image/");
}

bool Scene::isVisible(const Vector &point, const Light &light) const {
  Ray lightRay{light.position(), point - light.position()};
  double tLength{(light.position() - point).length()};
  if (auto lightHit = m_shapes.intersect(lightRay)) {
    return (tLength < lightHit->t() + 0.0001);
  }
  return true;
}

std::vector<Light> Scene::visibleLights(const Vector &point) const {
  std::vector<Light> visibleLights{};
  for (auto light : m_lights) {
    if (isVisible(point, light))
      visibleLights.push_back(light);
  }
  return visibleLights;
}

std::vector<Light> Scene::visibleLights(const Intersection &hit) const {
  return visibleLights(hit.position());
}
} // namespace raytracer
