#pragma once
#include "Vector.hpp"
#include <ostream>

class Sphere
{
private:
    Vector _origin;
    double _radius, _rs;

public:
    Sphere(Vector origin, double radius);
    Vector origin() const;
    double radius() const;
    double radiusSquare() const;
    bool contains(const Vector &point) const;

    friend std::ostream &operator<<(std::ostream &out, const Sphere &sphere);
};