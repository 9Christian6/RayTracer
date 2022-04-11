#pragma once
#include "Vector2.hpp"
#include "Ray2.hpp"
#include <optional>
#include <ostream>

namespace raytracer
{
    class Line2
    {
    private:
        Vector2 _p1, _p2;

    public:
        Line2(Vector2 p1, Vector2 p2);
        std::optional<Vector2> intersect(const Ray2 &ray);
        Vector2 p1() const;
        Vector2 p2() const;
        double length() const;
        bool contains(Vector2 &point) const;

        friend std::ostream &operator<<(std::ostream &out, const Line2 &ray);
    };
}