#pragma once
#include <ostream>
#include "Vector.hpp"
#include "Plane.hpp"

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
    bool isIn(const Plane &plane) const;

    // hit getters
    Vector getHit(const Vector &point) const;

    // point getters
    Vector getPoint(int length) const;
    Vector getPoint(double length) const;
    Vector getPoint(float length) const;

    friend std::ostream &operator<<(std::ostream &out, const Ray &ray);
};