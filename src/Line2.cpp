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
        Ray2 p{_p1, _p2 - _p1};
        double dx{ray.direction().x()};
        double dy{ray.direction().y()};
        double Px{p.origin().x()};
        double Pdx{p.direction().x()};
        double Py{p.origin().y()};
        double Pdy{p.direction().y()};
        double oy{ray.origin().y()};
        double ox{ray.origin().x()};
        if (p.direction().parallel(ray.direction()))
        {
            if (auto t = ray.getT(_p1))
                hitPoint = ray.getPoint(*t);
        }
        auto oneOverdx = scalarQuotient(dx, 1);
        auto oneOverPdyTimesPdxMinusdx = scalarQuotient(Pdy * (Pdx - dx), 1);
        double t = (Py + oy - (Px * *oneOverdx) + (ox * *oneOverdx)) * (dx * Pdy) * *oneOverPdyTimesPdxMinusdx;
        if (t >= 0)
            hitPoint = ray.getPoint(t);
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