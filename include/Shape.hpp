#pragma once
#include <optional>
#include "Color.hpp"
#include "Material.hpp"

namespace raytracer
{
    class Intersection;
    class Ray;
    class Shape
    {
    private:
    public:
        virtual ~Shape() = default;
        virtual std::optional<Intersection> intersect(const Ray &ray) const = 0;
    };
}