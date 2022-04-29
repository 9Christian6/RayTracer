#pragma once
#include "Shape.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include "Intersection.hpp"
#include <optional>

namespace raytracer
{
    class BoundingBox : public Shape
    {
    private:
    public:
        BoundingBox(Vector &minExt, Vector &maxExt);
        std::optional<Intersection> intersect(const Ray &ray);
    };
}