#include "Sphere.hpp"
#include "Ray.hpp"
#include "Intersection.hpp"
#include <math.h>
#include <optional>

namespace raytracer
{
    Vector Sphere::origin() const
    {
        return _origin;
    }

    double Sphere::radius() const
    {
        return _radius;
    }

    double Sphere::radiusSquare() const
    {
        return _rs;
    }

    Sphere::Sphere(Vector origin, double radius) : _origin{origin}, _radius{radius}
    {
        _rs = std::pow(_radius, 2);
    }

    bool Sphere::contains(const Vector &point) const
    {
        double xDiff{point.x() - _origin.x()};
        double yDiff{point.y() - _origin.y()};
        double zDiff{point.z() - _origin.z()};
        return (std::pow(xDiff, 2) + std::pow(yDiff, 2) + std::pow(zDiff, 2) == std::pow(_radius, 2));
    }

    std::optional<Intersection> Sphere::intersect(const Ray &ray)
    {
        std::optional<Intersection> hitPoint{};
        double B, C;
        B = ray.direction().x() * (ray.origin().x() - _origin.x());
        B += ray.direction().y() * (ray.origin().y() - _origin.y());
        B += ray.direction().z() * (ray.origin().z() - _origin.z());
        B *= 2;
        C = std::pow((ray.origin().x() - _origin.x()), 2);
        C += std::pow((ray.origin().y() - _origin.y()), 2);
        C += std::pow((ray.origin().z() - _origin.z()), 2);
        C -= std::pow(_radius, 2);
        double t{0};
        t = std::pow(B, 2) - (4 * C);
        if (t >= 0)
        {
            t = sqrt(t);
            t = -B - t;
            t /= 2;
            hitPoint.emplace(Intersection{ray});
            hitPoint.value().setT(t);
        }
        return hitPoint;
    }

    std::ostream &
    operator<<(std::ostream &out, const Sphere &sphere)
    {
        out << "Sphere\n o: " << sphere.origin() << " r: " << sphere.radius();
        return out;
    }
}