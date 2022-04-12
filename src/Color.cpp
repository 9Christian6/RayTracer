#include "Color.hpp"

namespace raytracer
{

    Color::Color(float r, float g, float b) : _r{r}, _g{g}, _b{b}
    {
    }

    Color Color::clamp(float min, float max) const
    {
        float newR{_r}, newG{_g}, newB{_b};
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

    float Color::r() const
    {
        return _r;
    }

    float Color::g() const
    {
        return _g;
    }
    float Color::b() const
    {
        return _b;
    }
}