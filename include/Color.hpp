#pragma once

namespace raytracer
{
    class Color
    {
    private:
        float _r, _g, _b;

    public:
        Color(float r, float g, float b);
        float r() const;
        float g() const;
        float b() const;

        Color clamp(float min, float max) const;

        friend Color operator+(const Color &lhs, const Color &rhs);
        friend Color operator*(const Color &lhs, const Color &rhs);
        friend Color operator*(const Color &op, float f);
    };
}