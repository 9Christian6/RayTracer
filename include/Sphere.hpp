#pragma once
#include "Vector.hpp"
#include "Shape.hpp"
#include <ostream>
#include <optional>

class Ray;
class Sphere : public Shape
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
    std::optional<Intersection> intersect(const Ray &ray);

    friend std::ostream &operator<<(std::ostream &out, const Sphere &sphere);
};