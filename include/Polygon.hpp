#pragma once
#include "Vector.hpp"
#include "Shape.hpp"
#include "Ray.hpp"
#include "Intersection.hpp"
#include "Line2.hpp"
#include <vector>
#include <optional>
#include <ostream>

namespace raytracer
{
    class Polygon : public Shape
    {
    private:
        std::vector<Vector> _points;

    public:
        Polygon() = delete;
        Polygon(std::vector<Vector> points);
        std::vector<Vector> points() const;
        std::optional<Intersection> intersect(const Ray &ray) override;
        friend std::ostream &operator<<(std::ostream &out, const Polygon &poly);
    };
}