#include "Camera.hpp"
#include "math.h"

Camera::Camera(Vector origin, Vector target, Vector upguide, double fov, double aspectRatio) : _position{origin}
{
    _forward = (target - origin).normalize();
    _right = _forward.cross(upguide).normalize();
    _up = _right.cross(_forward);
    h = std::tan(fov);
    w = h * aspectRatio;
};

Ray Camera::makeRay(Vector2 point) const
{
    Vector direction = _forward + point.x() * w * _right + point.y() * h * _up;
    return Ray{_position, direction.normalize()};
}