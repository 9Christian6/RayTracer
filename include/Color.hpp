#pragma once

namespace raytracer
{
    class Color
    {
    private:
        double _r, _g, _b;

    public:
        Color();
        Color(double r, double g, double b);
        float r() const
        {
            return _r;
        };
        float g() const
        {
            return _g;
        };
        float b() const
        {
            return _b;
        };

        Color clamp(float min, float max) const;

        friend Color operator+(const Color &lhs, const Color &rhs);
        Color operator+=(const Color &other);
        friend Color operator*(const Color &lhs, const Color &rhs);
        friend Color operator*(const Color &op, float f);
        Color operator*=(float f);
        bool operator==(const Color &color) const;
    };
}