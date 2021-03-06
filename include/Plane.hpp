#pragma once
#include <ostream>
#include "Vector.hpp"
#include "Shape.hpp"
#include "Material.hpp"
#include <optional>

namespace raytracer
{
    class Ray;
    class Plane : public Shape, public Material
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
        std::optional<Intersection> intersect(const Ray &ray) const override;
        friend std::ostream &operator<<(std::ostream &out, Plane &plane);
    };
}