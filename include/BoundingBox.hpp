#pragma once
#include "Vector.hpp"
#include "Ray.hpp"
#include "Plane.hpp"

namespace raytracer
{
    class BoundingBox
    {
    private:
        Vector _minExt, _maxExt;

    public:
        BoundingBox(Vector &&minExt, Vector &&maxExt);
        BoundingBox(Vector &minExt, Vector &&maxExt);
        BoundingBox(Vector &&minExt, Vector &maxExt);
        BoundingBox(Vector &minExt, Vector &maxExt);
        bool intersect(const Ray &ray);
    };
}