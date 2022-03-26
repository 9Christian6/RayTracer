#include "Plane.hpp"
#include "Exception.hpp"

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