#include "Color.hpp"

namespace raytracer
{

    Color::Color(float r, float g, float b) : _r{r}, _g{g}, _b{b}
    {
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