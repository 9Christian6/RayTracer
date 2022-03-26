#pragma once
#include "Point.hpp"

class Plane
{
private:
    Point _origin, _normal;

public:
    Plane(Point origin, Point normal);
};