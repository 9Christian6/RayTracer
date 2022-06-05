#pragma once
#include <optional>
#include "Color.hpp"
#include "Material.hpp"
#include "BoundingBox.hpp"

namespace raytracer
{
    class Intersection;
    class Ray;
    class Shape
    {
    private:
    protected:
        Shape() = default;
        Shape(BoundingBox bbox) : _BBox{bbox} {};
        BoundingBox _BBox;

    public:
        virtual ~Shape() = default;
        const BoundingBox &boundingBox() { return _BBox; };
        virtual std::optional<Intersection> intersect(const Ray &ray) const = 0;
    };
}