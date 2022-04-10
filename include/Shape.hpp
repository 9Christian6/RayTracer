#pragma once
#include <optional>

namespace raytracer
{
    class Intersection;
    class Ray;
    class Shape
    {
    private:
    public:
        virtual std::optional<Intersection> intersect(const Ray &ray) = 0;
    };
}