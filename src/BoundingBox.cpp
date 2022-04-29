#include "Exception.hpp"
#include "BoundingBox.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include <optional>

namespace raytracer
{
    BoundingBox::BoundingBox(Vector &minExt, Vector &maxExt) {}

    std::optional<Intersection> BoundingBox::intersect(const Ray &ray)
    {
        throw Exception{"Not Implemented"};
        return Intersection{ray};
    }
}