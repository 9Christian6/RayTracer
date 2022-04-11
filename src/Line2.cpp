#include "Line2.hpp"
#include "Vector2.hpp"
#include "Ray2.hpp"
#include "fEquals.hpp"
#include "SafeDivision.hpp"
#include "Exception.hpp"
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
        auto hit = std::optional<Vector2>();
        Ray2 line{_p1, _p2 - _p1};
        double length = (_p2 - _p1).length();
        if (line.direction().parallel(ray.direction()))
        {
            if (auto t = line.getT(ray.origin()))
                if (*t >= 0)
                    hit.emplace(line.scale(*t));
            return hit;
        }
        if (equals(line.direction().x(), 0))
        {
            double t = (line.origin().x() - ray.origin().x()) / ray.direction().x();
            auto hitPoint = ray.scale(t);
            if (contains(hitPoint) && t >= 0)
                hit.emplace(ray.scale(t));
        }
        if (!equals(line.direction().x(), 0))
        {
            double t = (line.origin().y() - ray.origin().y());
            t += (ray.origin().x() * line.direction().y()) / line.direction().x();
            t -= (line.origin().x() * line.direction().y()) / line.direction().x();
            t *= line.direction().x();
            t /= ray.direction().y() * line.direction().x() - ray.direction().x() * line.direction().y();
            auto hitPoint = ray.scale(t);
            if (contains(hitPoint) && t >= 0)
                hit.emplace(ray.scale(t));
        }
        return hit;
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

    bool Line2::contains(Vector2 &point) const
    {
        Ray2 line{_p1, _p2 - _p1};
        double length = (_p2 - _p1).length();
        if (auto lambda = line.getT(point))
            return (*lambda >= 0 && *lambda <= length);
        return false;
    }

    std::ostream &operator<<(std::ostream &out, const Line2 &line)
    {
        out << "Line\n[" << line.p1() << " to " << line.p2() << "]";
        out.flush();
        return out;
    }
}