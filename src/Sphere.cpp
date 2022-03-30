#include "Sphere.hpp"
#include "Ray.hpp"
#include "Intersection.hpp"
#include <math.h>

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

bool Sphere::doesIntersect(const Ray &ray)
{
    return ray.hit((*this)).has_value();
}

bool Sphere::intersect(Intersection &intersection)
{
    auto hitPoint = intersection.ray().hit(*this);
    if (hitPoint)
    {
        auto hitVec = (hitPoint.value() - intersection.ray().origin());
        intersection.setT(std::sqrt(hitVec.x() * hitVec.x() + hitVec.y() * hitVec.y() + hitVec.z() * hitVec.z()));
        return true;
    }
    return false;
}

std::ostream &
operator<<(std::ostream &out, const Sphere &sphere)
{
    out << "Sphere\n o: " << sphere.origin() << " r: " << sphere.radius();
    return out;
}