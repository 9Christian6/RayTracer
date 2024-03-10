#include "BoundingBox.hpp"
#include "Ray.hpp"
#include "Vector.hpp"
#include <algorithm>

namespace raytracer {
BoundingBox::BoundingBox(Vector &&minExt, Vector &&maxExt) {
  auto minX = std::min(minExt.x(), maxExt.x());
  auto minY = std::min(minExt.y(), maxExt.y());
  auto minZ = std::min(minExt.z(), maxExt.z());
  auto maxX = std::max(minExt.x(), maxExt.x());
  auto maxY = std::max(minExt.y(), maxExt.y());
  auto maxZ = std::max(minExt.z(), maxExt.z());
  m_min = {minX, minY, minZ};
  m_max = {maxX, maxY, maxZ};
}

BoundingBox::BoundingBox(Vector &minExt, Vector &&maxExt)
    : m_min{minExt}, m_max{std::move(maxExt)} {
  auto minX = std::min(minExt.x(), maxExt.x());
  auto minY = std::min(minExt.y(), maxExt.y());
  auto minZ = std::min(minExt.z(), maxExt.z());
  auto maxX = std::max(minExt.x(), maxExt.x());
  auto maxY = std::max(minExt.y(), maxExt.y());
  auto maxZ = std::max(minExt.z(), maxExt.z());
  m_min = {minX, minY, minZ};
  m_max = {maxX, maxY, maxZ};
}

BoundingBox::BoundingBox(Vector &&minExt, Vector &maxExt)
    : m_min{std::move(minExt)}, m_max{maxExt} {
  auto minX = std::min(minExt.x(), maxExt.x());
  auto minY = std::min(minExt.y(), maxExt.y());
  auto minZ = std::min(minExt.z(), maxExt.z());
  auto maxX = std::max(minExt.x(), maxExt.x());
  auto maxY = std::max(minExt.y(), maxExt.y());
  auto maxZ = std::max(minExt.z(), maxExt.z());
  m_min = {minX, minY, minZ};
  m_max = {maxX, maxY, maxZ};
}

BoundingBox::BoundingBox(Vector &minExt, Vector &maxExt)
    : m_min{minExt}, m_max{maxExt} {
  auto minX = std::min(minExt.x(), maxExt.x());
  auto minY = std::min(minExt.y(), maxExt.y());
  auto minZ = std::min(minExt.z(), maxExt.z());
  auto maxX = std::max(minExt.x(), maxExt.x());
  auto maxY = std::max(minExt.y(), maxExt.y());
  auto maxZ = std::max(minExt.z(), maxExt.z());
  m_min = {minX, minY, minZ};
  m_max = {maxX, maxY, maxZ};
}

Vector BoundingBox::minExt() const { return m_min; }

Vector BoundingBox::maxExt() const { return m_max; }

enum class Dimension { X, Y, Z };

bool BoundingBox::intersect(const Ray &ray) {
  auto dirfrac =
      raytracer::Vector{1 / ray.direction().x(), 1 / ray.direction().y(),
                        1 / ray.direction().z()};
  float t1 = (m_min.x() - ray.origin().x()) * dirfrac.x();
  float t2 = (m_max.x() - ray.origin().x()) * dirfrac.x();
  float t3 = (m_min.y() - ray.origin().y()) * dirfrac.y();
  float t4 = (m_max.y() - ray.origin().y()) * dirfrac.y();
  float t5 = (m_min.z() - ray.origin().z()) * dirfrac.z();
  float t6 = (m_max.z() - ray.origin().z()) * dirfrac.z();
  float tmin =
      std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
  float tmax =
      std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));
  if (tmax < 0) {
    return false;
  }
  if (tmin > tmax) {
    return false;
  }
  return true;
}
	
void BoundingBox::extend(const Vector &point) {
  double xMin{m_min.x()}, yMin{m_min.y()}, zMin{m_min.z()},
      xMax{m_max.x()}, yMax{m_max.y()}, zMax{m_max.z()};
  if (point.x() < xMin)
    xMin = point.x();
  if (point.y() < yMin)
    yMin = point.y();
  if (point.z() < zMin)
    zMin = point.z();
  if (point.x() > xMax)
    xMax = point.x();
  if (point.y() > yMax)
    yMax = point.y();
  if (point.z() > zMax)
    zMax = point.z();
  m_min = {xMin, yMin, zMin};
  m_max = {xMax, yMax, zMax};
}

void BoundingBox::extend(const BoundingBox& box){
  extend(box.minExt());
  extend(box.maxExt());
}

Dimension BoundingBox::longestDim() {
  auto xLen = maxExt().x() - minExt().x();
  auto yLen = maxExt().y() - minExt().y();
  auto zLen = maxExt().z() - minExt().z();
  if (xLen >= yLen && xLen >= zLen)
    return Dimension::X;
  if (yLen >= xLen && yLen >= zLen)
    return Dimension::Y;
  if (zLen >= xLen && zLen >= yLen)
    return Dimension::Z;
  throw std::logic_error("One dimension must be the shortest");
};

std::ostream &operator<<(std::ostream &stream, BoundingBox box) {
  stream << "MinExt: " << box.minExt() << ", MaxExt: " << box.maxExt();
  return stream;
}

} // namespace raytracer
