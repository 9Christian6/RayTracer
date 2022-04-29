#pragma once
#include "Color.hpp"

namespace raytracer
{
    class Material
    {
    private:
        Color _color;

    public:
        Material();
        Material(Color &Color);
        void setColor(Color color);
        Color color() const;
        Color reflects(const Color &color) const;
    };
}