#pragma once
#include <optional>
#include "Color.hpp"

namespace raytracer
{
    class Intersection;
    class Ray;
    class Shape
    {
    private:
        std::optional<Color> _color;

    public:
        inline void setColor(Color &color)
        {
            _color = color;
        };
        virtual std::optional<Intersection> intersect(const Ray &ray) = 0;
    };
}