#pragma once
#include "Color.hpp"
#include "Vector.hpp"
#include "Image.hpp"

namespace raytracer
{
    class Material
    {
    private:
        Color _color;
        double _specularity;
        Image _texture;

    public:
        Material();
        Material(Color &Color);
        Material(Color &color, double specularity);
        void setColor(Color color);
        void setTexture(const Image &img);
        const Image texture() const;
        void setSpecularity(double spec);
        double specularity() const;
        Color color() const;
        double reflects(const Vector &in, const Vector &out) const;
    };
}