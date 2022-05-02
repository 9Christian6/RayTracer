#pragma once
#include <ostream>
#include "Vector.hpp"
#include "Ray.hpp"
#include "Color.hpp"
#include "Light.hpp"
#include <vector>
#include <iostream>
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
        std::optional<Color> _color;

    public:
        Intersection(Ray &ray, Shape *shape);
        explicit Intersection(const Ray &ray);
        // Intersection(Ray &ray);
        bool intersected() const;
        void setT(double t);
        void setNormal(const Vector &norm);
        void setColor(const Color &color);
        Vector position() const;
        Vector normal() const;
        const Ray ray() const;
        double t() const;
        double angle() const;
        std::optional<Color> color(const std::vector<Light> &lights) const;
        double lambert(const Light &light) const;

        Intersection operator=(const Intersection &intersection) { return {intersection}; };
        friend std::ostream &operator<<(std::ostream &out, Intersection &intersection);
    };
}