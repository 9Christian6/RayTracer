#pragma once
#include "Color.hpp"

namespace raytracer
{
    class Material
    {
    private:
    public:
        Material();
        double reflects(const Color &color) const;
    };

    Material::Material()
    {
    }
}