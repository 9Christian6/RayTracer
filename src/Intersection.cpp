#include "Intersection.hpp"
#include "Ray.hpp"

Intersection::Intersection(const Ray &ray, const Shape &shape) : _ray{ray}
{
    _pShape = &shape;
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