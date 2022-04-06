#include "Intersection.hpp"
#include "Ray.hpp"

Intersection::Intersection(Ray &ray, Shape *shape) : _ray{ray}, _pShape{shape}
{
}

Intersection::Intersection(Ray &ray) : _ray{ray}, _t{Ray::RAY_T_MAX}, _pShape{NULL}
{
}

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

double Intersection::t() const
{
    return _t;
}

std::ostream &operator<<(std::ostream &out, Intersection &intersection)
{
    out << intersection.ray() << "\n"
        << intersection.t() << "\n"
        << intersection.position();
    return out;
}