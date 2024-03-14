#include "Shapeset.hpp"
#include <memory>
#include <vector>
#include <bvh/v2/bvh.h>
#include <bvh/v2/vec.h>
#include <bvh/v2/ray.h>
#include <bvh/v2/node.h>
#include <bvh/v2/default_builder.h>
#include <bvh/v2/thread_pool.h>
#include <bvh/v2/executor.h>
#include <bvh/v2/stack.h>
#include <bvh/v2/tri.h>

using Scalar  = float;
using Vec3    = bvh::v2::Vec<Scalar, 3>;
using BBox    = bvh::v2::BBox<Scalar, 3>;
using Tri     = bvh::v2::Tri<Scalar, 3>;
using Node    = bvh::v2::Node<Scalar, 3>;
using Bvh     = bvh::v2::Bvh<Node>;
using Ray     = bvh::v2::Ray<Scalar, 3>;
using PrecomputedTri = bvh::v2::PrecomputedTri<Scalar>;

namespace raytracer {

BVHNode::BVHNode(std::vector<Shape *> shapes)
    : m_bBox{std::make_shared<BoundingBox>()}, m_leftNode{{}}, m_rightNode{{}} {
  m_shapes = shapes;
}

void buildBVH(std::shared_ptr<BVHNode> leftNode,
              std::shared_ptr<BVHNode> rightNode, std::vector<Shape *> shapes) {
  // TODO build up BVH
}

std::tuple<std::vector<Shape *>,std::vector<Shape *>> seperateShapes(std::vector<Shape *> shapes){
  std::vector<Shape *> minShapes{}, maxShapes{};
  //TODO logic of seperation here
  return {minShapes, maxShapes};
}

void BVHNode::buildUp() {
  if (m_shapes.empty())
    return;
  for (auto shape : m_shapes)
    m_bBox->extend(shape->boundingBox());
  
  buildBVH(m_leftNode, m_rightNode, m_shapes);
}

ShapeSet::ShapeSet(std::vector<Shape *> &&shapes)
    : m_shapes{shapes}, m_leafNode{shapes} {
  m_leafNode.buildUp();
}

void ShapeSet::buildBVH() { m_leafNode.buildUp(); }

bool compareIntersection(const Intersection &lhs, const Intersection &rhs) {
  return lhs.t() < rhs.t();
}

void ShapeSet::addShape(Shape *shape) {
  m_shapes.push_back(shape);
  m_leafNode.m_shapes.push_back(shape);
}

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
