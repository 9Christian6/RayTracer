#pragma once
#include "Color.hpp"
#include "Vector.hpp"

namespace raytracer
{
    class Material
    {
    private:
        Color _color;
        Color m_Ka, m_Kd, m_Ks, m_Ns, m_Ni, m_d, m_illum;

    public:
        Material(Color Ka, Color Kd, Color Ks, Color Ns, Color Ni, Color d, Color illum);
        Material(Color &Color);
        Material(Color &color, double specularity);
	Material();
        void setColor(Color color);
        void setSpecularity(Color spec);
        Color specularity() const;
        Color ambientColor() const;
        double reflects(const Vector &in, const Vector &out) const;
    };
}
