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
    Vector2 v1{ray.origin() - _p1}, v2{_p2 - _p1}, v3{-ray.direction().y(), ray.direction().x()};
    if (v2 * v3 != 0)
    {
        double t;
        t = (std::sqrt(cross(v2, v1) * cross(v2, v1)) / (v2 * v3));
        if (t >= 0)
            hitPoint.emplace(ray.origin() + ray.direction() * t);
    }
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

std::ostream &operator<<(std::ostream &out, const Line2 &line)
{
    out << "Line\n[" << line.p1() << " to " << line.p2() << "]";
    out.flush();
    return out;
}