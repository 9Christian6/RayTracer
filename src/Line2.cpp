#include "Line2.hpp"
#include "Vector2.hpp"
#include "Ray2.hpp"
#include "fEquals.hpp"
#include "SafeDivision.hpp"
#include <optional>
#include <ostream>
#include <math.h>

namespace raytracer
{
    double cross(Vector2 p1, Vector2 p2)
    {
        return p1.x() * p2.y() - p1.y() * p2.x();
    }

    Line2::Line2(Vector2 p1, Vector2 p2) : _p1{p1}, _p2{p2} {};

    std::optional<Vector2> Line2::intersect(const Ray2 &ray)
    {
        std::optional<Vector2> hitPoint{};
        Ray2 line{_p1, _p2 - _p1};
        if (equals(ray.direction().x(), 0))
        {
            if (equals(ray.direction().y(), 0))
                return hitPoint;
            double t = line.origin().y() + line.direction().y() * ray.origin().x() - line.direction().y() * line.origin().x() - line.direction().x() * line.direction().y() - ray.origin().y();
            t /= ray.direction().y();
            hitPoint = ray.getPoint(t);
        }
        if (auto t = ray.getT(line.getPoint(0.5)))
            hitPoint = ray.getPoint(*t);
        double mu = ray.direction().x() * (ray.origin().y() - line.origin().y()) + ray.direction().y() * (line.origin().x() - ray.origin().x());
        mu /= ray.direction().x() * line.direction().y() - line.direction().x() * ray.direction().y();
        hitPoint = line.getPoint(mu);
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
}