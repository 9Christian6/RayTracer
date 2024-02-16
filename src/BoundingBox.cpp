#include "BoundingBox.hpp"
#include "Ray.hpp"
#include "Vector.hpp"
#include "fEquals.hpp"
#include <cfloat>
#include <limits>
#include <tuple>

namespace raytracer {
BoundingBox::BoundingBox(Vector &&minExt, Vector &&maxExt)
    : _minExt{std::move(minExt)}, _maxExt{std::move(maxExt)} {}

BoundingBox::BoundingBox(Vector &minExt, Vector &&maxExt)
    : _minExt{minExt}, _maxExt{std::move(maxExt)} {}

BoundingBox::BoundingBox(Vector &&minExt, Vector &maxExt)
    : _minExt{std::move(minExt)}, _maxExt{maxExt} {}

BoundingBox::BoundingBox(Vector &minExt, Vector &maxExt)
    : _minExt{minExt}, _maxExt{maxExt} {}

Vector BoundingBox::minExt() const { return _minExt; }

Vector BoundingBox::maxExt() const { return _maxExt; }

enum class Dimension { X, Y, Z };

bool hitTest(Dimension dim, const Ray &ray, double min, double max) {
  double tNear = std::numeric_limits<double>::lowest();
  double tFar = std::numeric_limits<double>::max();
  double rayO, rayD, t1, t2;
  switch (dim) {
    case Dimension::X:
    rayO = ray.origin().x();
    rayD = ray.direction().x();
    break;

    case Dimension::Y:
    rayO = ray.origin().y();
    rayD = ray.direction().y();
    break;

    case Dimension::Z:
    rayO = ray.origin().z();
    rayD = ray.direction().z();
    break;
  }
  t1 = (min - rayO) / rayD;
  t2 = (max - rayO) / rayD;
  if (t1 > t2)
    std::swap(t1, t2);
  if (t1 > tNear)
    tNear = t1;
  if (t2 < tFar)
    tFar = t2;
  if (tNear > tFar)
    return false;
  if (tFar < 0)
    return false;
  return true;
}

bool intersects1D(float origin, float direction, float minExt, float maxExt) {
  if (equals(minExt, maxExt))
    return true;
  double t_near = -DBL_MAX; // maximums defined in float.h
  double t_far = DBL_MAX;
  if (equals(direction, 0))
    if (origin > minExt && origin < maxExt)
      return true;
  auto T_1 = (minExt - origin) / direction;
  auto T_2 = (maxExt - origin) / direction;
  if (T_1 > T_2)
    std::swap(T_1, T_2);
  if (T_1 > t_near)
    t_near = T_1;
  if (T_2 < t_far)
    t_far = T_2;
  if (t_near > t_far || t_far < 0)
    return false;
  return true;
}

std::tuple<double, double> getTs(double rO, double rD, double min, double max) {
  auto t0 = (min - rO) / rD;
  auto t1 = (max - rO) / rD;
  if (t0 <= t1)
    return {t0, t1};
  return {t1, t0};
}

bool liesBetween(std::tuple<double, double> x, std::tuple<double, double> y) {
  return !(std::get<1>(x) < std::get<0>(y) || std::get<1>(y) < std::get<0>(x));
}

bool BoundingBox::intersect(const Ray &ray) {
  std::tuple<double, double> xTs(0, 1), yTs(0, 1), zTs(0, 1);
  if (!equals(ray.direction().x(), 0))
    xTs =
        getTs(ray.origin().x(), ray.direction().x(), _minExt.x(), _maxExt.x());
  if (!equals(ray.direction().y(), 0))
    yTs =
        getTs(ray.origin().y(), ray.direction().y(), _minExt.y(), _maxExt.y());
  if (!equals(ray.direction().z(), 0))
    zTs =
        getTs(ray.origin().z(), ray.direction().z(), _minExt.z(), _maxExt.z());
  auto xyHit = liesBetween(xTs, yTs);
  auto xzHit = liesBetween(xTs, zTs);
  auto yzHit = liesBetween(yTs, zTs);
  return xyHit && xzHit && yzHit;
}

void BoundingBox::extend(const Vector &point) {
  double xMin{_minExt.x()}, yMin{_minExt.y()}, zMin{_minExt.z()},
      xMax{_maxExt.x()}, yMax{_maxExt.y()}, zMax{_maxExt.z()};
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
  _minExt = {xMin, yMin, zMin};
  _maxExt = {xMax, yMax, zMax};
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

} // namespace raytracer
