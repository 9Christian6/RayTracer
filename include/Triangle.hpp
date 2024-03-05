#pragma once
#include <iostream>
#include <vector>
#include "Vector.hpp"
#include "Ray.hpp"
#include "OBJ_Loader.h"

namespace raytracer
{
    class Triangle : public Shape, public Material
    {
    private:

    public:
        Vector m_a, m_b, m_c, m_normal;
        Triangle() = delete;
        Triangle(Vector a, Vector b, Vector c);
        Triangle(objl::Vertex a, objl::Vertex b, objl::Vertex c);
        Triangle(std::vector<Vector> points);
        std::optional<Intersection> intersect(const Ray &ray) const override;
        friend std::ostream &operator<<(std::ostream &out, const Triangle &tri);
    };
}
