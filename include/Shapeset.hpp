#pragma once
#include "Shape.hpp"
#include "vector"
#include "Intersection.hpp"
#include "Light.hpp"
#include <optional>

namespace raytracer
{
    class ShapeSet : public Shape
    {
    protected:
        std::vector<Shape *> _shapes;
        std::vector<Light *> _lights;

    public:
        explicit ShapeSet(std::vector<Shape *> &&shapes);
        void addShape(Shape &shape);
        void addLight(Light &light);
        virtual std::optional<Intersection> intersect(const Ray &ray) const;
        std::vector<Intersection> visibleLights(const Vector &point);
    };
}