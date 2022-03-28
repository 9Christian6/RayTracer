#pragma once
#include "Vector.hpp"
#include "Ray.hpp"

class Camera
{
private:
    Vector _position, _forward, _up;

public:
    Camera();
    Ray makeRay(Vector point) const;
};