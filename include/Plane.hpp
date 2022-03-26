#pragma once
#include "Vector.hpp"

class Plane
{
private:
    Vector _origin, _normal;

public:
    Plane(Vector origin, Vector normal);
};