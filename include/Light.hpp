#pragma once
#include "Vector.hpp"

namespace raytracer
{
    class Light
    {
    private:
        Vector _position;

    public:
        explicit Light(Vector position);
        Vector position() const;
    };
}