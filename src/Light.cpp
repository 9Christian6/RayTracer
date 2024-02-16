#include "Light.hpp"

namespace raytracer
{
    Light::Light(Vector position) : _position{position} {}

    Vector Light::position() const
    {
        return _position;
    }
}