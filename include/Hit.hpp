#pragma once
#include "Vector.hpp"

namespace raytracer
{
    class Hit
    {
    private:
        Vector _position, _direction, _normal;

    public:
        Hit();
    };

    Hit::Hit()
    {
    }
}