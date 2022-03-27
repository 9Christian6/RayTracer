#include "Sphere.hpp"

Vector Sphere::origin() const
{
    return _origin;
}

pfrac::PrecisionFraction Sphere::radius() const
{
    return _radius;
}

Sphere::Sphere(Vector origin, pfrac::PrecisionFraction radius) : _origin{origin}, _radius{radius}
{
}