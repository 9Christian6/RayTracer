#include "Plane.hpp"
#include "Ray.hpp"
#include "Intersection.hpp"
#include "Exception.hpp"
#include "Vector.hpp"
#include <math.h>
#include <ostream>

Plane::Plane(Vector origin, Vector normal) : _origin{origin}, _normal{normal}
{
}

Vector Plane::normal() const
{
    return _normal;
}

Vector Plane::origin() const
{
    return _origin;
}

bool Plane::conatins(const Vector &point) const
{
    return _normal.orthogonal(_origin - point);
}

bool Plane::doesIntersect(const Ray &ray)
{
    return ray.hit((*this)).has_value();
}

bool Plane::intersect(Intersection &intersection)
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

std::ostream &operator<<(std::ostream &out, Plane &plane)
{
    out << "Plane\n origin: " << plane.origin() << "\nnormal: " << plane.normal() << "\n";
    return out;
}