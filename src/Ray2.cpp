#include "Ray2.hpp"
#include "Vector2.hpp"
#include "Exception.hpp"
#include "fEquals.hpp"
#include "SafeDivision.hpp"
#include <ostream>

namespace raytracer
{
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

    Vector2 Ray2::scale(double t) const
    {
        return _origin + (t * _direction);
    }

    std::optional<double> Ray2::getT(const Vector2 &point) const
    {
        std::optional<double> t;
        if (equals(_direction.x(), 0) && equals(_origin.x(), point.x()))
            return scalarQuotient(_direction.y(), point.y() - _origin.y());
        if (equals(_direction.y(), 0) && equals(point.y(), _origin.y()))
            return scalarQuotient(_direction.x(), point.x() - _origin.x());
        auto t1 = scalarQuotient(_direction.x(), point.x() - _origin.x());
        auto t2 = scalarQuotient(_direction.y(), point.y() - _origin.y());
        if (t1 && t2 && (equals(*t1, *t2)))
            t = t1;
        return t;
    }

    std::ostream &operator<<(std::ostream &out, const Ray2 &ray)
    {
        out << "Ray2\n o: " << ray.origin() << ", d: " << ray.direction();
        out.flush();
        return out;
    }
}