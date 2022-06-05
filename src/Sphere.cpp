#include "Sphere.hpp"
#include "Ray.hpp"
#include "Intersection.hpp"
#include "BoundingBox.hpp"
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

    Sphere::Sphere(Vector origin, double radius) : Shape{{origin, origin}}, _origin{origin}, _radius{radius}
    {
        _rs = std::pow(_radius, 2);
        _BBox = BoundingBox{_origin - Vector{radius, radius, radius}, _origin + Vector{radius, radius, radius}};
    }

    bool Sphere::contains(const Vector &point) const
    {
        double xDiff{point.x() - _origin.x()};
        double yDiff{point.y() - _origin.y()};
        double zDiff{point.z() - _origin.z()};
        return (std::pow(xDiff, 2) + std::pow(yDiff, 2) + std::pow(zDiff, 2) == std::pow(_radius, 2));
    }

    std::optional<Intersection> Sphere::intersect(const Ray &ray) const
    {
        if (_BBox.intersect(ray))
        {
            double B, C;
            B = ray.direction().x() * (ray.origin().x() - _origin.x());
            B += ray.direction().y() * (ray.origin().y() - _origin.y());
            B += ray.direction().z() * (ray.origin().z() - _origin.z());
            B *= 2;
            C = std::pow((ray.origin().x() - _origin.x()), 2);
            C += std::pow((ray.origin().y() - _origin.y()), 2);
            C += std::pow((ray.origin().z() - _origin.z()), 2);
            C -= std::pow(_radius, 2);
            double t = std::pow(B, 2) - (4 * C);
            if (t > Ray::RAY_T_MIN && t < Ray::RAY_T_MAX)
            {
                t = sqrt(t);
                t = -B - t;
                if (t <= 0)
                    return {};
                t /= 2;
                Vector hit = ray.getPoint(t);
                Vector normal = (hit - _origin).normalize();
                double angle = normal.angle(ray.direction());
                Material mat = static_cast<Material>(*this);
                return Intersection{ray, t, normal, color(), angle, mat};
            }
        }
        return {};
    }

    // BoundingBox Sphere::boundingBox()
    // {
    //     return BoundingBox{_origin - Vector{1, 1, 1} * _radius, _origin + Vector{1, 1, 1} * _radius};
    // }

    std::ostream &
    operator<<(std::ostream &out, const Sphere &sphere)
    {
        out << "Sphere\n o: " << sphere.origin() << " r: " << sphere.radius();
        return out;
    }
}