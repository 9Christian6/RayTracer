#pragma once
#include <ostream>
#include "Vector.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"

class Ray
{
private:
    Vector _origin, _direction;

public:
    Ray(Vector origin, Vector direction);

    // accessors
    Vector origin() const;
    Vector direction() const;

    // hit testers
    bool hit(const Vector &point) const;
    bool hit(const Plane &plane) const;
    bool hit(const Sphere &sphere) const;
    bool isIn(const Plane &plane) const;

    // hit getters
    Vector getHit(const Vector &point) const;
    Vector getHit(const Plane &plane) const;

    // point getters
    Vector getPoint(int length) const;
    Vector getPoint(double length) const;
    Vector getPoint(float length) const;
    Vector getPoint(pfrac::PrecisionFraction length) const;

    friend std::ostream &operator<<(std::ostream &out, const Ray &ray);
};