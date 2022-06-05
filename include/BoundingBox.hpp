#pragma once
#include "Vector.hpp"

namespace raytracer
{
    class Ray;
    class BoundingBox
    {
    private:
        Vector _minExt, _maxExt;

    public:
        BoundingBox() = default;
        BoundingBox(Vector &&minExt, Vector &&maxExt);
        BoundingBox(Vector &minExt, Vector &&maxExt);
        BoundingBox(Vector &&minExt, Vector &maxExt);
        BoundingBox(Vector &minExt, Vector &maxExt);
        Vector minExt() const;
        Vector maxExt() const;
        bool intersect(const Ray &ray);
    };
}