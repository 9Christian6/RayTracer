#include "Material.hpp"

namespace raytracer
{
    Material::Material(Color Ka, Color Kd, Color Ks, Color Ns, Color Ni, Color d, Color illum) : m_Ka{Ka}, m_Kd{Kd}, m_Ns{Ns}, m_Ni{Ni}, m_d{d}, m_illum{illum}{};

    Material::Material() : _color(Color{1, 1, 1}), m_Ka{Color{1, 1, 1}}, m_Kd{Color{1, 1, 1}}, m_Ks{Color{1, 1, 1}}, m_Ns{Color{1, 1, 1}}, m_Ni{Color{1, 1, 1}}, m_d{Color{1, 1, 1}}, m_illum{Color{1, 1, 1}} {};

    Material::Material(Color &color) : _color(color){};

    double Material::reflects(const Vector &in, const Vector &out) const
    {
        return in.angle(out) / 180.;
    }

    Color Material::specularity() const
    {
        return m_Ks;
    }

    Color Material::ambientColor() const
    {
        return m_Ka;
    }

    void Material::setColor(Color color)
    {
        _color = color;
    }

    void Material::setSpecularity(Color spec)
    {
        m_Ka = spec;
    }
}
