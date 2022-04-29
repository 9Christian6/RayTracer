#include "Material.hpp"

namespace raytracer
{
    Material::Material() : _color(Color{1, 1, 1}){};

    Material::Material(Color &color) : _color(color){};

    Color Material::reflects(const Color &color) const
    {
        return (_color * color).clamp(0, 1);
    }

    Color Material::color() const
    {
        return Color{_color};
    }

    void Material::setColor(Color color)
    {
        _color = color;
    }
}