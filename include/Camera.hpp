#pragma once
#include "Vector.hpp"
#include "Vector2.hpp"
#include "Ray.hpp"
#include "Image.hpp"

class Camera
{
private:
    Vector _position, _forward, _up, _right;
    double h, w;

public:
    Camera(Vector position, Vector forward, Vector up, double fov, double aspectRatio);
    Ray makeRay(const Image img, const Vector2 point) const;
};