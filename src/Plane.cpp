#include "Plane.hpp"
#include "Ray.hpp"
#include "Intersection.hpp"
#include "Exception.hpp"
#include "Vector.hpp"
#include <math.h>
#include <ostream>
#include <optional>

namespace raytracer
{
    Plane::Plane(Vector origin, Vector normal) : _origin{origin}, _normal{normal.normalize()}
    {
    }

    Plane::Plane(Vector A, Vector B, Vector C)
    {
        if (A == B || A == C || B == C)
            throw Exception{"Plane needs 3 unique points"};
        if (Ray{A, (B - A)}.hit(C))
            throw Exception{"Points must not lie on one line"};
        _normal = (B - A).cross(C - A).normalize();
        _origin = A;
    }

    Vector Plane::normal() const
    {
        return _normal;
    }

    Vector Plane::origin() const
    {
        return _origin;
    }

    double Plane::A() const
    {
        return _normal.x();
    }

    double Plane::B() const
    {
        return _normal.y();
    }

    double Plane::C() const
    {
        return _normal.z();
    }

    double Plane::D() const
    {
        return _normal * _origin;
    }

    bool Plane::conatins(const Vector &point) const
    {
        return _normal.orthogonal(_origin - point);
    }

    std::optional<Intersection> Plane::intersect(const Ray &ray) const
    {
        std::optional<Intersection> hit{};
        Intersection hitPoint{ray};
        double denom{_normal * ray.direction()};
        if (denom == 0 && !conatins(ray.origin()))
            return {};
        if (denom == 0 && conatins(ray.origin()))
        {
            return Intersection{ray, 1, _normal, color(), _normal.angle(ray.direction())};
        }
        double t = ((_origin - ray.origin()) * _normal) / denom;
        if (t <= Ray::RAY_T_MIN || t >= Ray::RAY_T_MAX)
        {
            return {};
        }
        return Intersection{ray, t, _normal, color(), _normal.angle(ray.direction())};
    }

    std::ostream &operator<<(std::ostream &out, Plane &plane)
    {
        out << "Plane\norigin: " << plane.origin() << "\nnormal: " << plane.normal() << "\n";
        return out;
    }
}