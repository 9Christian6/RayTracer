#include "Ray.hpp"
#include "Exception.hpp"

Ray::Ray(Vector origin, Vector direction) : _origin{origin}, _direction{direction}
{
    if (direction == Vector{0, 0, 0})
        throw Exception{"Direction can't be zero"};
    _direction = _direction.normalize();
}

Vector Ray::origin() const
{
    return _origin;
}

Vector Ray::direction() const
{
    return _direction;
}

bool hitx(const Ray &ray, const Vector &point)
{
    return ray.origin() == point;
}

bool hity(const Ray &ray, const Vector &point)
{
    return ray.origin() == point;
}

bool hitz(const Ray &ray, const Vector &point)
{
    return ray.origin() == point;
}

bool hitxy(const Ray &ray, const Vector &point)
{
    if (ray.direction().x() == 0)
        return true;
    // return hity(ray, point);
    if (ray.direction().y() == 0)
        return true;
    // return hitx(ray, point);
    pfrac::PrecisionFraction lambdax, lambday;
    lambdax = (point.x() - ray.origin().x()) / ray.direction().x();
    lambday = (point.y() - ray.origin().y()) / ray.direction().y();
    return lambdax == lambday;
}

bool hitxz(const Ray &ray, const Vector &point)
{
    if (ray.direction().x() == 0)
        return true;
    // return hitz(ray, point);
    if (ray.direction().z() == 0)
        return true;
    // return hitx(ray, point);
    pfrac::PrecisionFraction lambdax, lambdaz;
    lambdax = (point.x() - ray.origin().x()) / ray.direction().x();
    lambdaz = (point.z() - ray.origin().z()) / ray.direction().z();
    return lambdax == lambdaz;
}

bool hityz(const Ray &ray, const Vector &point)
{
    if (ray.direction().y() == 0)
        return true;
    // return hitz(ray, point);
    if (ray.direction().z() == 0)
        return true;
    // return hity(ray, point);
    pfrac::PrecisionFraction lambday, lambdaz;
    lambday = (point.y() - ray.origin().y()) / ray.direction().y();
    lambdaz = (point.z() - ray.origin().z()) / ray.direction().z();
    return lambday == lambdaz;
}

bool Ray::hit(const Vector &point) const
{
    if (_direction.x() == 0)
        return hityz(*this, point);
    if (_direction.y() == 0)
        return hitxz(*this, point);
    if (_direction.z() == 0)
        return hitxy(*this, point);
    pfrac::PrecisionFraction lambdax, lambday, lambdaz;
    lambdax = (point.x() - _origin.x()) / _direction.x();
    lambday = (point.y() - _origin.y()) / _direction.y();
    lambdaz = (point.z() - _origin.z()) / _direction.z();
    return ((lambdax == lambday) && (lambday == lambdaz) && (lambdax == lambdaz));
}

bool Ray::hit(const Plane &plane) const
{
    if (_direction * plane.normal() == 0)
        return (plane.conatins(_origin));
    return true;
}

bool Ray::hit(const Sphere &sphere) const
{
    // pfrac::PrecisionFraction A{_direction.x().square() + _direction.y().square() + _direction.z().square()};
    pfrac::PrecisionFraction B{_direction.x() * (_origin.x() - sphere.origin().x())};
    B += _direction.y() * (_origin.y() - sphere.origin().y());
    B += _direction.z() * (_origin.z() - sphere.origin().z());
    B *= 2;
    pfrac::PrecisionFraction C{(_origin.x() - sphere.origin().x()).square()};
    C += (_origin.y() - sphere.origin().y()).square();
    C += (_origin.z() - sphere.origin().z()).square();
    C -= sphere.radius().square();
    return ((B.square() - 4 * C) >= 0);
}

bool Ray::isIn(const Plane &plane) const
{
    if (plane.conatins(_origin))
    {
        return plane.normal() * _direction == 0;
    }
    return false;
}

Vector Ray::getHit(const Vector &point) const
{
    if (hit(point))
    {
        if (_direction.x() != 0)
        {
            return _origin + _direction * ((point.x() - _origin.x()) / _direction.x());
        }
        if (_direction.y() != 0)
        {
            return _origin + _direction * ((point.y() - _origin.y()) / _direction.y());
        }
        if (_direction.z() != 0)
        {
            return _origin + _direction * ((point.z() - _origin.z()) / _direction.z());
        }
    }
    throw Exception{"getHit was called without the Ray hitting the point"};
}

Vector Ray::getHit(const Plane &plane) const
{
    if (!hit(plane))
        throw Exception{"getHit was called without Ray hitting plane"};
    if (isIn(plane))
        return _origin;
    pfrac::PrecisionFraction denom{plane.normal() * _direction};
    pfrac::PrecisionFraction t{((plane.origin() - _origin) * plane.normal()) / denom};
    return getPoint(t);
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

Vector Ray::getPoint(pfrac::PrecisionFraction length) const
{
    return _origin + (_direction * length);
}

std::ostream &operator<<(std::ostream &out, const Ray &ray)
{
    out << "origin: " << ray.origin() << ", direction: " << ray.direction();
    return out;
}