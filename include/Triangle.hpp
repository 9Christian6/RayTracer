#pragma once
#include <iostream>
#include <vector>
#include "Vector.hpp"
#include "Ray.hpp"

namespace raytracer
{
    class Triangle : public Shape, public Material
    {
    private:
        Vector m_a, m_b, m_c, m_normal;

    public:
        Triangle() = delete;
        Triangle(Vector a, Vector b, Vector c);
        Triangle(std::vector<Vector> points);
        std::optional<Intersection> intersect(const Ray &ray) const override;
        friend std::ostream &operator<<(std::ostream &out, const Triangle &tri);
    };
}