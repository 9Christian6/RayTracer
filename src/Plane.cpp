#include "Plane.hpp"
#include "Ray.hpp"
#include "Intersection.hpp"
#include "Exception.hpp"
#include "Vector.hpp"
#include <math.h>
#include <ostream>
#include <optional>

Plane::Plane(Vector origin, Vector normal) : _origin{origin}, _normal{normal}
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

std::optional<Intersection> Plane::intersect(const Ray &ray)
{
    std::optional<Intersection> hit{};
    if (ray.direction() * _normal == 0 && !conatins(ray.origin()))
        return hit;
    double denom{_normal * ray.direction()};
    double t{((_origin - ray.origin()) * _normal) / denom};
    if (t <= 0)
    {
        Intersection hitPoint{ray};
        hitPoint.setT(t);
        hit.emplace(hitPoint);
    }
    return hit;
    // auto hitPoint = intersection.ray().hit(*this);
    // if (hitPoint)
    // {
    //     auto hitVec = (hitPoint.value() - intersection.ray().origin());
    //     intersection.setT(std::sqrt(hitVec.x() * hitVec.x() + hitVec.y() * hitVec.y() + hitVec.z() * hitVec.z()));
    //     return true;
    // }
    // return false;
}

std::ostream &operator<<(std::ostream &out, Plane &plane)
{
    out << "Plane\n origin: " << plane.origin() << "\nnormal: " << plane.normal() << "\n";
    return out;
}