#pragma once
#include <ostream>
#include "Vector.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include <optional>

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
    std::optional<Vector> hit(const Vector &point) const;
    std::optional<Vector> hit(const Plane &plane) const;
    std::optional<Vector> hit(const Sphere &sphere) const;
    bool isIn(const Plane &plane) const;

    // point getters
    Vector getPoint(int length) const;
    Vector getPoint(double length) const;
    Vector getPoint(float length) const;
    Vector getPoint(pfrac::PrecisionFraction length) const;

    friend std::ostream &operator<<(std::ostream &out, const Ray &ray);
};