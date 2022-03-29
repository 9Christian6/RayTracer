#pragma once
#include "Shape.hpp"
#include "vector"

class ShapeSet : public Shape
{
protected:
    std::vector<Shape *> shapes;

public:
    ShapeSet();
    void addShape(Shape *shape);
};