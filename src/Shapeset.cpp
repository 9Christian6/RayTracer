#include "Shapeset.hpp"

void ShapeSet::addShape(Shape &shape)
{
    _shapes.push_back(&shape);
}

std::optional<Intersection> ShapeSet::intersect(const Ray &ray)
{
    for (auto shape : _shapes)
    {
        if (auto hitPoint = shape->intersect(ray))
            return hitPoint;
    }
    return std::optional<Intersection>{};
}