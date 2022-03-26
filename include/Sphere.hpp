#pragma once
#include "Vector.hpp"

class Sphere
{
private:
    Vector _origin;
    pfrac::PrecisionFraction _radius;

public:
    Sphere(Vector origin, pfrac::PrecisionFraction radius);
};

Sphere::Sphere(Vector origin, pfrac::PrecisionFraction radius) : _origin{origin}, _radius{radius}
{
}