#include "Camera.hpp"
#include "Image.hpp"
#include "math.h"
#include <ostream>

namespace raytracer
{
    Camera::Camera(Vector origin, Vector target, Vector upguide, double fov, double aspectRatio) : _position{origin}
    {
        target = origin + target;
        upguide = origin + upguide;
        _forward = (target - origin).normalize();
        _right = _forward.cross(upguide).normalize();
        _up = _right.cross(_forward);
        h = std::tan(fov);
        w = h * aspectRatio;
    };

    Ray Camera::makeRay(int width, int height, const Vector2 point) const
    {
        double xR = ((point.x() / (double)width) * 2) - 1;
        double yR = ((point.y() / (double)height) * 2) - 1;
        Vector direction = _forward + xR * w * _right + yR * h * _up;
        return Ray{_position, direction.normalize()};
    }

    Vector Camera::position() const
    {
        return _position;
    }

    void Camera::setPosition(const Vector &position, const Vector &upguide, const Vector &forward)
    {
        _position = position;
        _up = upguide;
        _forward = forward;
    }

    Vector Camera::direction() const
    {
        return _forward;
    }

    std::ostream &operator<<(std::ostream &out, const Camera &cam)
    {
        out << "Camera\nPosition: " << cam.position() << "\nDirection: " << cam.direction() << "\n";
        return out;
    }
}