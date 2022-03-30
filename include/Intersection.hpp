#pragma once
#include "Vector.hpp"
#include "Ray.hpp"
#include <memory>

class Shape;

class Intersection
{
private:
    const Ray &_ray;
    double _t;
    const Shape *_pShape;

public:
    Intersection(const Ray &ray, const Shape &shape);
    Intersection(const Ray &ray);
    bool intersected() const;
    Vector position();
};