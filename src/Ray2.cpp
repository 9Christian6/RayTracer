#include "Ray2.hpp"
#include "Vector2.hpp"
#include "Exception.hpp"
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

std::ostream &operator<<(std::ostream &out, const Ray2 &ray)
{
    out << "Ray2\n o: " << ray.origin() << ", d: " << ray.direction();
    out.flush();
    return out;
}