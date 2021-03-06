#pragma once
#include "Vector2.hpp"
#include <optional>
#include <ostream>

namespace raytracer
{
    class Ray2
    {
    private:
        Vector2 _origin, _direction;

    public:
        Ray2(Vector2 origin, Vector2 direction);

        Vector2 origin() const;
        Vector2 direction() const;
        Vector2 scale(double t) const;
        std::optional<double> getT(const Vector2 &point) const;
        friend std::ostream &operator<<(std::ostream &out, const Ray2 &ray);
    };
}