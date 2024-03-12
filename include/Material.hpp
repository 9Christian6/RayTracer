#pragma once
#include "Color.hpp"
#include "OBJ_Loader.h"
#include "Vector.hpp"

namespace raytracer
{
    class Material
    {
    private:
        Color _color;
        Color m_Ka, m_Kd, m_Ks;
	float m_Ns, m_Ni, m_d, m_illum;

    public:
        Material(Color Ka, Color Kd, Color Ks, float Ns, float Ni, float d, float illum);
        Material(Color &Color);
        Material(Color &color, double specularity);
	Material();
	void setColor(Color Ka, Color Kd, Color Ks, float Ns, float Ni, float d, float illum);
	void SetMaterial(objl::Material mat);
        Color Ka() const;
	Color Kd() const;
        Color Ks() const;
	float Ns() const;
	float Ni() const;
	float d() const;
	float illum() const;
        double reflects(const Vector &in, const Vector &out) const;
    };
}
