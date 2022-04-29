#pragma once
#include <optional>
#include "Color.hpp"
#include "Material.hpp"

namespace raytracer
{
    class Intersection;
    class Ray;
    class Shape : public Material
    {
    private:
    public:
        virtual ~Shape() = default;
        virtual std::optional<Intersection> intersect(const Ray &ray) = 0;
    };
}