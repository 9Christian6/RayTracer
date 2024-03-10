#include <Intersection.hpp>
#include <Triangle.hpp>

namespace raytracer {
Triangle::Triangle(Vector a, Vector b, Vector c) : m_a(a), m_b(b), m_c(c) {
  m_normal = (m_c - m_a).cross(m_c - m_b).normalize();
  m_bbox = BoundingBox{m_a, m_b};
  m_bbox.extend(m_c);
}

Triangle::Triangle(objl::Vertex a, objl::Vertex b, objl::Vertex c) {
  m_a = Vector{a.Position.X, a.Position.Y, a.Position.Z};
  m_b = Vector{b.Position.X, b.Position.Y, b.Position.Z};
  m_c = Vector{c.Position.X, c.Position.Y, c.Position.Z};
  m_normal = (m_c - m_a).cross(m_c - m_b).normalize();
  m_bbox = BoundingBox{m_a, m_b};
  m_bbox.extend(m_c);
}

std::optional<Intersection> Triangle::intersect(const Ray &ray) const {
  const float EPSILON = 0.0000001;
  Vector vertex0 = m_a;
  Vector vertex1 = m_b;
  Vector vertex2 = m_c;
  Vector edge1, edge2, h, s, q;
  float a, f, u, v;
  edge1 = vertex1 - vertex0;
  edge2 = vertex2 - vertex0;
  h = ray.direction().cross(edge2);
  a = edge1 * h;
  if (a > -EPSILON && a < EPSILON)
    return {}; // This ray is parallel to this triangle.
  f = 1.0 / a;
  s = ray.origin() - vertex0;
  u = f * s * h;
  if (u < 0.0 || u > 1.0)
    return {};
  q = s.cross(edge1);
  v = f * ray.direction() * q;
  if (v < 0.0 || u + v > 1.0)
    return {};
  // At this stage we can compute t to find out where the intersection point is
  // on the line.
  float t = f * edge2 * q;
  if (t > EPSILON) {
    // ray intersection
  auto angle = m_normal * ray.direction();
    if (angle <= 0 || angle > 90)
      return Intersection{ray, t, -m_normal, ambientColor(),
                          ray.direction() * -m_normal};
    return Intersection{ray, t, m_normal, ambientColor(), ray.direction() * m_normal};
  }
  // This means that there is a line intersection but not a ray intersection.
  return {};
}

Triangle::Triangle(std::vector<Vector> points) {
  if (points.size() == 3) {
    m_a = points.at(0);
    m_b = points.at(1);
    m_c = points.at(2);
  }
  m_bbox = BoundingBox{points[0], points[1]};
  m_bbox.extend(points[2]);
  m_normal = (m_a - m_b).cross(m_c - m_b).normalize();
}
} // namespace raytracer
