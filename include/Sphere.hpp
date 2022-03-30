#pragma once
#include "Vector.hpp"
#include "Shape.hpp"
#include <ostream>

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
    bool doesIntersect(const Ray &ray) override;
    bool intersect(Intersection &intersection) override;

    friend std::ostream &operator<<(std::ostream &out, const Sphere &sphere);
};