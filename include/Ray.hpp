#pragma once
#include <ostream>
#include "Vector.hpp"
#include "Vector2.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include <optional>

class Ray
{
private:
    Vector _origin, _direction;

public:
    Ray(Vector origin, Vector direction);
    Ray(Vector2 origin, Vector2 direction);

    // constants
    static constexpr double RAY_T_MIN = 1.001;
    static constexpr double RAY_T_MAX = 1.0e30;

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

    Ray operator=(const Ray &ray);
    friend std::ostream &operator<<(std::ostream &out, const Ray &ray);
};