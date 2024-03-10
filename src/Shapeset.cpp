#include "Shapeset.hpp"
#include <memory>
#include <vector>

namespace raytracer {

enum class Dimension { X, Y, Z };

struct BVHNode {
  bool m_isLeaf;
  std::shared_ptr<BoundingBox> m_bBox;
  std::shared_ptr<BVHNode> m_leftNode, m_rightNode;
  std::vector<Shape *> m_shapes;

public:
  explicit BVHNode(std::vector<Shape *> &&shapes) { m_shapes = shapes; };
  bool intersect(Ray &ray);
  Dimension longestDim();
};

void buildBVH(std::shared_ptr<BVHNode> leftNode,
              std::shared_ptr<BVHNode> rightNode, std::vector<Shape *> shapes) {
  // TODO build up BVH
}

struct BVH {
  std::shared_ptr<BVHNode> m_leftNode, m_rightNode;

public:
  BVH(std::vector<Shape *> &&shapes) {
    buildBVH(m_leftNode, m_rightNode, shapes);
  };
};

ShapeSet::ShapeSet(std::vector<Shape *> &&shapes) : _shapes{shapes} {}

bool compareIntersection(const Intersection &lhs, const Intersection &rhs) {
  return lhs.t() < rhs.t();
}

void ShapeSet::addShape(Shape *shape) { _shapes.push_back(shape); }

void ShapeSet::addLight(Light &light) { _lights.push_back(&light); }

std::optional<Intersection> ShapeSet::intersect(const Ray &ray) const {
  std::vector<Intersection> hits;
  for (auto shape : _shapes) {
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
