#pragma once
#include <optional>

#include "BoundingBox.hpp"

namespace raytracer
{
    class Intersection;
    class Ray;
    class Shape
    {
    protected:
        BoundingBox m_bbox;

    private:
    public:
        inline BoundingBox boundingBox() const { return m_bbox; };
        virtual ~Shape() = default;
        virtual std::optional<Intersection> intersect(const Ray &ray) const = 0;
    };
} // namespace raytracer
