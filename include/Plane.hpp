#pragma once
#include "Vector.hpp"

class Plane
{
private:
    Vector _origin, _normal;

public:
    Plane(Vector origin, Vector normal);

    Vector origin() const;
    Vector normal() const;

    bool conatins(const Vector &point) const;
};