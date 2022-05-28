#include "Material.hpp"

namespace raytracer
{
    Material::Material() : _color(Color{1, 1, 1}), _specularity{1} {};

    Material::Material(Color &color) : _color(color){};

    Material::Material(Color &color, double specularity) : _color(color), _specularity(specularity){};

    double Material::reflects(const Vector &in, const Vector &out) const
    {
        return in.angle(out) / 180.;
    }

    Color Material::color() const
    {
        return Color{_color};
    }

    void Material::setColor(Color color)
    {
        _color = color;
    }

    void Material::setSpecularity(double spec)
    {
        _specularity = spec;
    }
}