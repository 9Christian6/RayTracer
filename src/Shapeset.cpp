#include "Shapeset.hpp"

void ShapeSet::addShape(Shape &shape)
{
    _shapes.push_back(&shape);
}