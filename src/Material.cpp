#include "Material.hpp"

namespace raytracer
{
    Material::Material(Color Ka, Color Kd, Color Ks, float Ns, float Ni, float d, float illum) : m_Ka{Ka}, m_Kd{Kd}, m_Ns{Ns}, m_Ni{Ni}, m_d{d}, m_illum{illum}{};

    Material::Material() : _color(Color{1, 1, 1}), m_Ka{Color{1, 1, 1}}, m_Kd{Color{1, 1, 1}}, m_Ks{Color{1, 1, 1}}, m_Ns{0}, m_Ni{1}, m_d{1}, m_illum{1} {};

    Material::Material(Color &color) : _color(color){};

    double Material::reflects(const Vector &in, const Vector &out) const
    {
        return in.angle(out) / 180.;
    }

    void Material::setColor(Color Ka, Color Kd, Color Ks, float Ns, float Ni, float d, float illum){
      m_Ka = Ka;
      m_Kd = Kd;
      m_Ks = Ks;
      m_Ns = Ns;
      m_Ni = Ni;
      m_d = d;
      m_illum = illum;
    }

    void Material::SetMaterial(objl::Material mat){
      m_Ka = mat.Ka; 
      m_Kd = mat.Kd;
      m_Ks = mat.Ks;
      m_Ns = mat.Ns;
      m_Ni = mat.Ni;
      m_d = mat.d;
      m_illum = mat.illum;
 
    }

    Color Material::Ka() const
    {
        return m_Ka;
    }

    Color Material::Kd() const
    {
        return m_Kd;
    }

    Color Material::Ks() const
    {
        return m_Ks;
    }

    float Material::Ns() const
    {
        return m_Ns;
    }

    float Material::Ni() const
    {
        return m_Ni;
    }

    float Material::d() const
    {
        return m_d;
    }

    float Material::illum() const
    {
        return m_illum;
    }
}
