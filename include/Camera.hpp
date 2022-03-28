#pragma once
#include "Vector.hpp"
#include "Vector2.hpp"
#include "Ray.hpp"

class Camera
{
private:
    Vector _position, _forward, _up, _right;
    double h, w;

public:
    Camera(Vector origin, Vector target, Vector upguide, double fov, double aspectRatio);
    Ray makeRay(Vector2 point) const;
};