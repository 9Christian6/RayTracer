#include "Camera.hpp"
#include "Image.hpp"
#include "math.h"

Camera::Camera(Vector origin, Vector target, Vector upguide, double fov, double aspectRatio) : _position{origin}
{
    _forward = (target - origin).normalize();
    _right = _forward.cross(upguide).normalize();
    _up = _right.cross(_forward);
    h = std::tan(fov);
    w = h * aspectRatio;
};

Ray Camera::makeRay(const Image img, const Vector2 point) const
{
    double xR = (2 * point.x()) / (double)img.width() - 1;
    double yR = (2 * point.y()) / (double)img.height() - 1;
    Vector direction = _forward + xR * w * _right + yR * h * _up;
    return Ray{_position, direction.normalize()};
}