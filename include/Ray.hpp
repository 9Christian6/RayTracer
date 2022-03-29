#pragma once
#include <ostream>
#include "Vector.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include <optional>

#define RAY_T_MIN = 1.001f;
#define RAY_T_MAX = 1.0e30f;

class Ray
{
private:
    Vector _origin, _direction;

public:
    Ray(Vector origin, Vector direction);

    // accessors
    Vector origin() const;
    Vector direction() const;

    // hit getters
    std::optional<Vector> hit(const Vector &point) const;
    std::optional<Vector> hit(const Plane &plane) const;
    std::optional<Vector> hit(const Sphere &sphere) const;
    bool isIn(const Plane &plane) const;

    // point getters
    Vector getPoint(int length) const;
    Vector getPoint(double length) const;
    Vector getPoint(float length) const;

    friend std::ostream &operator<<(std::ostream &out, const Ray &ray);
};