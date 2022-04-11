#include "Ray.hpp"
#include "Intersection.hpp"
#include "Polygon.hpp"
#include "Exception.hpp"
#include "Plane.hpp"
#include "Vector.hpp"
#include "Vector2.hpp"
#include "Line2.hpp"
#include "Ray2.hpp"
#include <iostream>
#include <vector>

namespace raytracer
{
    Polygon::Polygon(std::vector<Vector> points) : _points(points)
    {
        auto plane = Plane{_points.at(0), _points.at(1), _points.at(2)};
        for (auto point : _points)
        {
            if (!plane.conatins(point))
                throw Exception{"Not all points lie in one plane"};
        }
    }

    std::optional<Intersection> Polygon::intersect(const Ray &ray)
    {
        Plane plane{_points.at(0), _points.at(1), _points.at(2)};
        if (!plane.intersect(ray))
            return std::optional<Intersection>{};
        auto hit = plane.intersect(ray).value();
        double nX{std::abs(plane.normal().x())}, nY{std::abs(plane.normal().y())}, nZ{std::abs(plane.normal().z())};
        int dimToLoose;
        if (nX >= nY && nX >= nZ)
        {
            dimToLoose = 0;
        }
        if (nY >= nX && nY >= nZ)
        {
            dimToLoose = 1;
        }
        if (nZ >= nX && nZ >= nY)
        {
            dimToLoose = 2;
        }
        std::optional<Intersection> hitPoint;
        auto projectedHit = hit.position().project(dimToLoose);
        int intersectionCount = 0;
        Ray2 testRay{projectedHit, Vector2{1, 0}};
        std::vector<Line2> lines;
        Vector2 p0 = _points[0].project(dimToLoose);
        Vector2 lastPoint = _points.at(_points.size() - 1).project(dimToLoose);
        lines.push_back(Line2{p0, lastPoint});
        for (size_t i = 1; i < _points.size(); i++)
        {
            Vector2 p1{_points[i - 1].project(dimToLoose)}, p2{_points[i].project(dimToLoose)};
            lines.push_back(Line2{p1, p2});
        }
        for (auto line : lines)
            if (auto hit = line.intersect(testRay))
            {
                intersectionCount++;
            }
        if (intersectionCount % 2 == 1)
        {
            hitPoint.emplace(hit);
        }
        return hitPoint;
    }

    std::vector<Vector> Polygon::points() const
    {
        return _points;
    }

    std::ostream &operator<<(std::ostream &out, const Polygon &poly)
    {
        std::vector<Vector> points = poly.points();
        out << "Polygon\n"
            << points.at(0);
        for (size_t i = 1; i < poly.points().size(); i++)
        {
            out << ", " << points.at(i);
        }
        out << "\n";
        return out;
    }
}