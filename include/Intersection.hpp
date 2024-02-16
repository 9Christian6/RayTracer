#pragma once
#include <ostream>
#include "Material.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include "Color.hpp"
#include "Light.hpp"
#include <vector>
#include <iostream>
#include <memory>

namespace raytracer
{
    const static double HIT_EPSILON = 0.5;
    class Shape;
    class Intersection
    {
    private:
        const Ray &_ray;
        double _t, _angle;
        Shape *_pShape;
        Vector _position, _normal;
        const std::optional<Material> _material;
        std::optional<Color> _color;

    public:
        Intersection(Ray &ray, Shape *shape);
        explicit Intersection(const Ray &ray);
        explicit Intersection(const Ray &ray, double t, const Vector &normal, const Color &color, double angle);
        explicit Intersection(const Ray &ray, double t, const Vector &normal, const Color &color, double angle, Material &material);
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
        std::optional<Material> material() const;
        Ray reflectionRay() const;
        Intersection operator=(const Intersection &intersection) { return {intersection}; };
        bool operator<(const Intersection &intersection);
        friend std::ostream &operator<<(std::ostream &out, Intersection &intersection);
    };
}