#include "Ray2.hpp"
#include "Vector2.hpp"
#include "Exception.hpp"
#include "fEquals.hpp"
#include "SafeDivision.hpp"
#include <ostream>
Ray2::Ray2(Vector2 origin, Vector2 direction) : _origin{origin}, _direction{direction}
{
    if (direction == Vector2{0, 0})
        throw Exception{"Direction can't be zero"};
    _direction = _direction.normalize();
};

Vector2 Ray2::origin() const
{
    return Vector2{_origin};
}

Vector2 Ray2::direction() const
{
    return Vector2{_direction};
}

Vector2 Ray2::getPoint(double t) const
{
    return _origin + (t * _direction);
}

std::optional<double> Ray2::getT(const Vector2 &point) const
{
    if (raytracer::equals(_direction.x(), 0) && raytracer::equals(point.x(), 0))
        return raytracer::scalarQuotient(_direction.y(), point.y() - _origin.y());
    if (raytracer::equals(_direction.y(), 0) && raytracer::equals(point.y(), 0))
        return raytracer::scalarQuotient(_direction.x(), point.x() - _origin.x());
    std::optional<double> t;
    auto t1 = raytracer::scalarQuotient(_direction.x(), point.x() - _origin.x());
    auto t2 = raytracer::scalarQuotient(_direction.y(), point.y() - _origin.y());
    if (t1 && t2 && (raytracer::equals(*t1, *t2)))
        t = t1;
    return t;
}

std::ostream &operator<<(std::ostream &out, const Ray2 &ray)
{
    out << "Ray2\n o: " << ray.origin() << ", d: " << ray.direction();
    out.flush();
    return out;
}