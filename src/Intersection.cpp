#include "Intersection.hpp"
#include "Ray.hpp"
#include <math.h>

namespace raytracer
{
    Intersection::Intersection(Ray &ray, Shape *shape) : _ray{ray}, _pShape{shape}
    {
    }

    // Intersection::Intersection(Ray &ray) : _ray{ray}, _t{Ray::RAY_T_MAX}, _pShape{NULL}
    // {
    // }

    Intersection::Intersection(const Ray &ray) : _ray{ray}, _t{Ray::RAY_T_MAX}, _pShape{NULL}
    {
    }

        bool Intersection::intersected() const
    {
        return (_pShape != NULL);
    }

    Vector Intersection::position()
    {
        return _ray.getPoint(_t);
    }

    const Ray Intersection::ray() const
    {
        return _ray;
    }

    void Intersection::setT(double t)
    {
        _t = t;
        _position = _ray.getPoint(t);
    }

    void Intersection::setNormal(const Vector &norm)
    {
        _normal = norm;
        double num = _normal * _ray.direction();
        _angle = std::acos(num) * 180.0 / 3.14159265;
    }

    double Intersection::t() const
    {
        return _t;
    }

    double Intersection::angle() const
    {
        return _angle;
    }

    std::ostream &operator<<(std::ostream &out, Intersection &intersection)
    {
        out << intersection.ray() << "\n"
            << intersection.t() << "\n"
            << intersection.position();
        return out;
    }
}