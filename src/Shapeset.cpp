#include "Shapeset.hpp"
#include <memory>
#include <vector>

namespace raytracer {

void buildBVH(std::shared_ptr<BVHNode> leftNode,
              std::shared_ptr<BVHNode> rightNode, std::vector<Shape *> shapes) {

  // TODO build up BVH
}

ShapeSet::ShapeSet(std::vector<Shape *> &&shapes) : m_shapes{shapes}, m_leafNode{shapes}{
}

bool compareIntersection(const Intersection &lhs, const Intersection &rhs) {
  return lhs.t() < rhs.t();
}

void ShapeSet::addShape(Shape *shape) { m_shapes.push_back(shape); m_leafNode.m_shapes.push_back(shape);}

void ShapeSet::addLight(Light &light) { _lights.push_back(&light); }

std::optional<Intersection> ShapeSet::intersect(const Ray &ray) const {
  std::vector<Intersection> hits;
  for (auto shape : m_shapes) {
    if (!shape->boundingBox().intersect(ray))
      continue;
    if (auto hitPoint = shape->intersect(ray)) {
      hits.insert(std::lower_bound(hits.begin(), hits.end(), hitPoint.value()),
                  hitPoint.value());
    }
  }
  return hits.size() == 0 ? std::optional<Intersection>() : hits[0];
}

std::vector<Intersection> ShapeSet::visibleLights(const Vector &point) {
  std::vector<Intersection> visibleLights;
  for (auto light : _lights) {
    auto lightRay = Ray{point, light->position() - point};
    auto hit = intersect(lightRay);
    if (!hit)
      visibleLights.push_back(*hit);
  }
  return visibleLights;
}
} // namespace raytracer
