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
        void setColor(Color color);
        Color color() const;
        double reflects(const Vector &in, const Vector &out) const;
    };
}