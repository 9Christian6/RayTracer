#pragma once
#include "Shape.hpp"
#include "vector"
#include "Intersection.hpp"
#include <optional>

namespace raytracer
{
    class ShapeSet : public Shape
    {
    protected:
        std::vector<Shape *> _shapes;

    public:
        void addShape(Shape &shape);
        virtual std::optional<Intersection> intersect(const Ray &ray);
    };
}