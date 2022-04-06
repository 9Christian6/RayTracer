#include "Line2.hpp"
#include "Vector2.hpp"
#include "Ray2.hpp"
#include <optional>
#include <ostream>
#include <math.h>

double cross(Vector2 p1, Vector2 p2)
{
    return p1.x() * p2.y() - p1.y() * p2.x();
}

Line2::Line2(Vector2 p1, Vector2 p2) : _p1{p1}, _p2{p2} {};

std::optional<Vector2> Line2::intersect(const Ray2 &ray)
{
    std::optional<Vector2> hitPoint{};
    Ray2 line{_p1, _p2 - _p1};
    double d1x{ray.direction().x()}, d1y{ray.direction().y()}, o1x{ray.origin().x()}, o1y{ray.origin().y()};
    double d2x{line.direction().x()}, d2y{line.direction().y()}, o2x{line.origin().x()}, o2y{line.origin().y()};
    double t = (o1y + ((d1y * o2x) / d1x) - ((d1y * o1x) / d1x) - o2y);
    t = t / (d2y - ((d1y * d2x) / d1x));
    if (t < (_p2 - _p1).length())
        hitPoint.emplace(line.getPoint(t));
    return hitPoint;
}

Vector2 Line2::p1() const
{
    return Vector2{_p1};
}

Vector2 Line2::p2() const
{
    return Vector2{_p2};
}

double Line2::length() const
{
    Vector2 line = _p2 - _p1;
    return line.length();
}

std::ostream &operator<<(std::ostream &out, const Line2 &line)
{
    out << "Line\n[" << line.p1() << " to " << line.p2() << "]";
    out.flush();
    return out;
}