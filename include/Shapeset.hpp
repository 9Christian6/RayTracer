#pragma once
#include "Intersection.hpp"
#include "Light.hpp"
#include "Shape.hpp"
#include "vector"
#include <memory>
#include <optional>

namespace raytracer {
enum class Dimension { X, Y, Z };

struct BVHNode {
  bool m_isLeaf;
  std::shared_ptr<BoundingBox> m_bBox;
  std::shared_ptr<BVHNode> m_leftNode, m_rightNode;
  std::vector<Shape *> m_shapes;

public:
  //explicit BVHNode(std::vector<Shape *> &&shapes) { m_shapes = shapes; };
  explicit BVHNode(std::vector<Shape *> shapes) { m_shapes = shapes; };
  bool intersect(Ray &ray);
  Dimension longestDim();
};

class ShapeSet : public Shape {
private:
  BVHNode m_leafNode;
protected:
  std::vector<Shape *> m_shapes;
  std::vector<Light *> _lights;

public:
  explicit ShapeSet(std::vector<Shape *> &&shapes);
  void addShape(Shape *shape);
  void addLight(Light &light);
  virtual std::optional<Intersection> intersect(const Ray &ray) const;
  std::vector<Intersection> visibleLights(const Vector &point);
};
} // namespace raytracer
