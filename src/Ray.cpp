#include <iostream>
#include <math.h>
#include "Ray.hpp"
#include "Exception.hpp"
#include <optional>

namespace raytracer
{
    Ray::Ray(Vector origin, Vector direction) : _origin{origin}, _direction{direction}
    {
        if (direction == Vector{0, 0, 0})
            throw Exception{"Direction can't be zero"};
        _direction = _direction.normalize();
    }

    Ray::Ray(Vector2 origin, Vector2 direction) : _origin{origin.x(), origin.y(), 0.}, _direction{Vector{direction.x(), direction.y(), 0.}}
    {
    }

    Vector Ray::origin() const
    {
        return _origin;
    }

    Vector Ray::direction() const
    {
        return _direction;
    }

    std::optional<Vector> hitx(const Ray &r, const Vector &p)
    {
        std::optional<Vector> hit = {};
        if (r.direction().x() > 0)
            hit.emplace(r.getPoint((p.x() - r.origin().x()) / r.direction().x()));
        return hit;
    }

    std::optional<Vector> hity(const Ray &r, const Vector &p)
    {
        std::optional<Vector> hit = {};
        if (r.direction().y() > 0)
            hit.emplace(r.getPoint((p.y() - r.origin().y()) / r.direction().y()));
        return hit;
    }

    std::optional<Vector> hitz(const Ray &r, const Vector &p)
    {
        std::optional<Vector> hit = {};
        if (r.direction().z() > 0)
            hit.emplace(r.getPoint((p.z() - r.origin().z()) / r.direction().z()));
        return hit;
    }

    std::optional<Vector> hitxy(const Ray &r, const Vector &p)
    {
        std::optional<Vector> hit = {};
        if (p.z() != 0)
            return hit;
        if (r.direction().y() == 0)
            return hitx(r, p);
        if (r.direction().x() == 0)
            return hity(r, p);
        double t0 = (p.x() - r.origin().x()) / r.direction().x();
        double t1 = (p.y() - r.origin().y()) / r.direction().y();
        if (t0 == t1)
            hit.emplace(r.getPoint(t0));
        return hit;
    }

    std::optional<Vector> hitxz(const Ray &r, const Vector &p)
    {
        std::optional<Vector> hit = {};
        if (p.y() != 0)
            return hit;
        if (r.direction().x() == 0)
            return hitz(r, p);
        if (r.direction().z() == 0)
            return hitx(r, p);
        double t0 = (p.x() - r.origin().x()) / r.direction().x();
        double t1 = (p.z() - r.origin().z()) / r.direction().z();
        if (t0 == t1)
            hit.emplace(r.getPoint(t0));
        return hit;
    }

    std::optional<Vector> hityz(const Ray &r, const Vector &p)
    {
        std::optional<Vector> hit = {};
        if (p.x() != 0)
            return hit;
        if (r.direction().y() == 0)
            return hitx(r, p);
        if (r.direction().z() == 0)
            return hity(r, p);
        double t0 = (p.z() - r.origin().z()) / r.direction().z();
        double t1 = (p.y() - r.origin().y()) / r.direction().y();
        if (t0 == t1)
            hit.emplace(r.getPoint(t0));
        return hit;
    }

    std::optional<Vector> Ray::hit(const Vector &p) const
    {
        std::optional<Vector> hit = {};
        if (_direction.x() == 0)
            return hityz((*this), p);
        if (_direction.y() == 0)
            return hitxz((*this), p);
        if (_direction.z() == 0)
            return hitxy((*this), p);
        double t0 = (p.x() - _origin.x()) / _direction.x();
        double t1 = (p.y() - _origin.y()) / _direction.y();
        double t2 = (p.z() - _origin.z()) / _direction.z();
        if (t0 == t1 && t0 == t2 && t1 == t2)
            hit.emplace(getPoint(t0));
        return hit;
    }

    std::optional<Vector> Ray::hit(const Sphere &sphere) const
    {
        std::optional<Vector> hitPoint;
        double B, C;
        B = _direction.x() * (_origin.x() - sphere.origin().x());
        B += _direction.y() * (_origin.y() - sphere.origin().y());
        B += _direction.z() * (_origin.z() - sphere.origin().z());
        B *= 2;
        C = std::pow((_origin.x() - sphere.origin().x()), 2);
        C += std::pow((_origin.y() - sphere.origin().y()), 2);
        C += std::pow((_origin.z() - sphere.origin().z()), 2);
        C -= std::pow(sphere.radius(), 2);
        double t{0};
        t = std::pow(B, 2) - (4 * C);
        if (t >= 0)
        {
            t = sqrt(t);
            t = -B - t;
            t /= 2;
            hitPoint.emplace(getPoint(t));
        }
        return hitPoint;
    }

    std::optional<Vector> Ray::hit(const Plane &plane) const
    {
        std::optional<Vector> hit = {};
        if (_direction * plane.normal() == 0 && !plane.conatins(_origin))
            return hit;
        double denom{plane.normal() * _direction};
        double t{((plane.origin() - _origin) * plane.normal()) / denom};
        if (t <= 0)
            hit.emplace(getPoint(t));
        return hit;
    }

    bool Ray::isIn(const Plane &plane) const
    {
        if (plane.conatins(_origin))
        {
            return plane.normal() * _direction == 0;
        }
        return false;
    }

    Vector Ray::getPoint(int length) const
    {
        return _origin + (_direction * length);
    }

    Vector Ray::getPoint(double length) const
    {
        return _origin + (_direction * length);
    }

    Vector Ray::getPoint(float length) const
    {
        return _origin + (_direction * length);
    }

    Ray Ray::operator=(const Ray &ray)
    {
        return Ray{_origin, _direction};
    }

    std::ostream &operator<<(std::ostream &out, const Ray &ray)
    {
        out << "Ray\n o: " << ray.origin() << ", d: " << ray.direction();
        return out;
    }
}