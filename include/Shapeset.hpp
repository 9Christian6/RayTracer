#pragma once
#include "Shape.hpp"
#include "vector"

class ShapeSet : public Shape
{
protected:
    std::vector<Shape *> _shapes;

public:
    ShapeSet();
    void addShape(Shape &shape);
};