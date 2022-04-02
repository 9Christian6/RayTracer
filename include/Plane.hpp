#pragma once
#include <ostream>
#include "Vector.hpp"
#include "Shape.hpp"

class Ray;
class Plane : public Shape
{
private:
    Vector _origin, _normal;

public:
    Plane() = delete;
    Plane(Vector origin, Vector normal);
    Plane(Vector A, Vector B, Vector C);

    Vector origin() const;
    Vector normal() const;
    double A() const;
    double B() const;
    double C() const;
    double D() const;

    bool conatins(const Vector &point) const;
    bool doesIntersect(const Ray &ray) override;
    bool intersect(Intersection &intersection) override;
    friend std::ostream &operator<<(std::ostream &out, Plane &plane);
};