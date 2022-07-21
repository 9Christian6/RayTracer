#include "Color.hpp"

namespace raytracer
{

    // Color::Color(float r, float g, float b) : _r{r}, _g{g}, _b{b}
    // {
    // }

    Color::Color(double r, double g, double b) : _r{r}, _g{g}, _b{b}
    {
    }

    Color::Color() : _r{1}, _g{1}, _b{1}
    {
    }

    Color Color::clamp(float min, float max) const
    {
        double newR{_r}, newG{_g}, newB{_b};
        if (_r < min)
            newR = min;
        if (_r > max)
            newR = max;
        if (_g < min)
            newG = min;
        if (_g > max)
            newG = max;
        if (_b < min)
            newB = min;
        if (_b > max)
            newB = max;
        return Color{newR, newG, newB};
    }

    Color operator+(const Color &lhs, const Color &rhs)
    {
        return Color(lhs.r() + rhs.r(), lhs.g() + rhs.g(), lhs.b() + rhs.b());
    }

    Color Color::operator+=(const Color &other)
    {
        _r = _r + other.r();
        _g = _g + other.g();
        _b = _b + other.b();
        return *this;
    }

    Color operator*(const Color &lhs, const Color &rhs)
    {
        return Color(lhs.r() * rhs.r(), lhs.g() * rhs.g(), lhs.b() * rhs.b());
    }

    Color operator*(const Color &lhs, float f)
    {
        return Color(lhs.r() * f, lhs.g() * f, lhs.b() * f);
    }

    Color Color::operator*=(float f)
    {
        *this = *this * f;
        return *this;
    }

    bool Color::operator==(const Color &color) const
    {
        return (_r == color.r()) && (_b == color.b()) && (_g == color.g());
    }
}