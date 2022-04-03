#pragma once
#include <ostream>
#include "Vector.hpp"
#include "Shape.hpp"
#include <optional>

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
    std::optional<Intersection> intersect(const Ray &ray) override;
    friend std::ostream &operator<<(std::ostream &out, Plane &plane);
};