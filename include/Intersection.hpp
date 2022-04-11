#pragma once
#include <ostream>
#include "Vector.hpp"
#include "Ray.hpp"
#include <memory>

namespace raytracer
{
    class Shape;

    class Intersection
    {
    private:
        const Ray &_ray;
        double _t, _angle;
        Shape *_pShape;
        Vector _position, _normal;

    public:
        Intersection(Ray &ray, Shape *shape);
        Intersection(const Ray &ray);
        Intersection(Ray &ray);
        bool intersected() const;
        void setT(double t);
        void setNormal(const Vector &norm);
        Vector position();
        const Ray ray() const;
        double t() const;
        double angle() const;
        friend std::ostream &operator<<(std::ostream &out, Intersection &intersection);
    };
}