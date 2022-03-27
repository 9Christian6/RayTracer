#pragma once
#include "Vector.hpp"

class Sphere
{
private:
    Vector _origin;
    pfrac::PrecisionFraction _radius, _rs;

public:
    Sphere(Vector origin, pfrac::PrecisionFraction radius);
    Vector origin() const;
    pfrac::PrecisionFraction radius() const;
    pfrac::PrecisionFraction radiusSquare() const;
    bool contains(const Vector &point) const;

    friend ostream &operator<<(ostream &out, const Sphere &sphere);
};