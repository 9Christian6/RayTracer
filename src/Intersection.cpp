#include "Intersection.hpp"
#include "Ray.hpp"
#include "Color.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include <vector>
#include <math.h>

namespace raytracer
{
    Intersection::Intersection(Ray &ray, Shape *shape) : _ray{ray}, _pShape{shape}
    {
    }

    Intersection::Intersection(const Ray &ray) : _ray{ray}, _t{Ray::RAY_T_MAX}, _pShape{NULL}
    {
    }

    bool Intersection::intersected() const
    {
        return (_pShape != NULL);
    }

    Vector Intersection::position() const
    {
        return _ray.getPoint(_t);
    }

    Vector Intersection::normal() const
    {
        return Vector{_normal};
    }

    const Ray Intersection::ray() const
    {
        return _ray;
    }

    std::optional<Color> Intersection::color(const std::vector<Light> &lights) const
    {
        double brightness{0};
        if (_color)
        {
            Color color{*_color};
            for (auto light : lights)
            {
                brightness += lambert(light);
            }
            color = color * (brightness / lights.size()) * 0.85;
            return color;
        }
        return {};
    }

    double Intersection::lambert(const Light &light) const
    {
        double brightness{0};
        auto lightDirection = (light.position() - _position).normalize();
        brightness = _normal * lightDirection;
        return brightness;
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

    void Intersection::setColor(const Color &color)
    {
        _color = color;
    }

    void Intersection::setMaterial(const Material &material)
    {
        _material = material;
    }

    double Intersection::t() const
    {
        return _t;
    }

    double Intersection::angle() const
    {
        return _angle;
    }

    Ray Intersection::reflectionRay() const
    {
        return Ray{_position, _ray.direction().reflect(_normal)};
    }

    std::ostream &operator<<(std::ostream &out, Intersection &intersection)
    {
        out << intersection.ray() << "\n"
            << intersection.t() << "\n"
            << intersection.position();
        return out;
    }
}