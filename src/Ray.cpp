#include "Ray.hpp"
#include "Exception.hpp"
#include <Eigen/Core>

Ray::Ray(Vector origin, Vector direction) : _origin{origin}, _direction{direction}
{
    if (direction == Vector{0, 0, 0})
        throw Exception{"Direction can't be zero"};
}

Vector Ray::origin() const
{
    return _origin;
}

Vector Ray::direction() const
{
    return _direction;
}

bool Ray::hit(Vector point) const
{
    pfrac::PrecisionFraction lambdax, lambday, lambdaz;
    if (_direction.x() != 0)
    {
        lambdax = (point.x() - _origin.x()) / _direction.x();
    }
    else if (point.x() != _origin.x())
        return false;

    if (_direction.y() != 0)
    {
        lambday = (point.y() - _origin.y()) / _direction.y();
    }
    else if (point.y() != _origin.y())
        return false;

    if (_direction.z() != 0)
    {
        lambdaz = (point.z() - _origin.z()) / _direction.z();
    }
    else if (point.z() != _origin.z())
        return false;
    return ((lambdax == lambday) && (lambday == lambdaz));
}

bool Ray::hit(Plane plane) const
{
    throw Exception{"Not Implemented"};
}

Vector Ray::getPoint(int length) const
{
    return _origin + (_direction * length);
}

Vector Ray::getPoint(double length) const
{
    return _origin + (_direction * length);
}

Vector Ray::getPoint(float length) const
{
    return _origin + (_direction * length);
}

std::ostream &operator<<(std::ostream &out, const Ray &ray)
{
    out << "origin: " << ray.origin() << ", direction: " << ray.direction();
    return out;
}