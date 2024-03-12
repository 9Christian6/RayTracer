#pragma once
#include <string>
#include "OBJ_Loader.h"

namespace raytracer
{
    class Color
    {
    private:
        float _r, _g, _b;

    public:
        Color(float r, float g, float b);
	Color(objl::Vector3 Kd);
        Color() = default;
        Color clamp(float min, float max) const;
        float r() const;
        float g() const;
        float b() const;
        std::string getColorTriplet() const;
        friend Color operator+(const Color &lhs, const Color &rhs);
        Color operator+=(const Color &other);
        friend Color operator*(const Color &lhs, const Color &rhs);
        friend Color operator*(const Color &op, float f);
        Color operator*=(float f);
    };
}
