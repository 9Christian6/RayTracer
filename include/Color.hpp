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
    };
}