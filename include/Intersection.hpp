#pragma once
#include <ostream>
#include "Vector.hpp"
#include "Ray.hpp"
#include <memory>

class Shape;

class Intersection
{
private:
    const Ray &_ray;
    double _t;
    Shape *_pShape;

public:
    Intersection(Ray &ray, Shape *shape);
    Intersection(const Ray &ray);
    Intersection(Ray &ray);
    bool intersected() const;
    void setT(double t);
    Vector position();
    const Ray ray() const;
    double t() const;
    friend std::ostream &operator<<(std::ostream &out, Intersection &intersection);
};