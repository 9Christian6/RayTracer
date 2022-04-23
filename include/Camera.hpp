#pragma once
#include "Vector.hpp"
#include "Vector2.hpp"
#include "Ray.hpp"
#include <ostream>

namespace raytracer
{
    class Camera
    {
    private:
        Vector _position, _forward, _up, _right;
        double h, w;

    public:
        Camera(Vector position, Vector forward, Vector up, double fov, double aspectRatio);
        Vector position() const;
        void setPosition(const Vector &position, const Vector &upguide, const Vector &forward);
        Vector direction() const;
        Ray makeRay(int imgWidth, int imgHeight, const Vector2 point) const;
        friend std::ostream &operator<<(std::ostream &out, const Camera &cam);
    };
}