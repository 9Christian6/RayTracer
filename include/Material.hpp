#pragma once
#include "Color.hpp"
#include "Vector.hpp"

namespace raytracer
{
    class Material
    {
    private:
        Color _color;
        double _specularity;

    public:
        Material();
        Material(Color &Color);
        Material(Color &color, double specularity);
        void setColor(Color color);
        void setSpecularity(double spec);
        double specularity() const;
        Color color() const;
        double reflects(const Vector &in, const Vector &out) const;
    };
}