#pragma once
#include "Shape.hpp"
#include "vector"
#include "Intersection.hpp"

class ShapeSet : public Shape
{
protected:
    std::vector<Shape *> _shapes;

public:
    void addShape(Shape &shape);

    virtual bool intersect(Intersection &intersection);
    virtual bool doesIntersect(const Ray &ray);
};