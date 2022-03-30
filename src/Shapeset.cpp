#include "Shapeset.hpp"

void ShapeSet::addShape(Shape &shape)
{
    _shapes.push_back(&shape);
}

bool ShapeSet::doesIntersect(const Ray &ray)
{
    for (auto shape : _shapes)
    {
        if (shape->doesIntersect(ray))
            return true;
    }
    return false;
}

bool ShapeSet::intersect(Intersection &intersection)
{
    bool doesIntersect = false;
    for (auto shape : _shapes)
    {
        if (shape->intersect(intersection))
            doesIntersect = true;
    }
    return doesIntersect;
}