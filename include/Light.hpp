#pragma once
#include "Vector.hpp"

namespace raytracer
{
    class Light
    {
    private:
        const Vector _position;

    public:
        Light(Vector &direction);
        Vector position() const;
    };
}