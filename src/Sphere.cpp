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

bool Sphere::contains(const Vector &point) const
{
    pfrac::PrecisionFraction xDiff{point.x() - _origin.x()};
    pfrac::PrecisionFraction yDiff{point.y() - _origin.y()};
    pfrac::PrecisionFraction zDiff{point.z() - _origin.z()};
    return (xDiff.square() + yDiff.square() + zDiff.square() == _radius.square());
}

ostream &
operator<<(ostream &out, const Sphere &sphere)
{
    out << "o: " << sphere.origin() << " r: " << sphere.radius();
    return out;
}