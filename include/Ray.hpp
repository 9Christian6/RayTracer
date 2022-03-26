#pragma once
#include <ostream>
#include "Point.hpp"

class Ray
{
private:
    Point _origin, _direction;

public:
    Ray(Point origin, Point direction);

    // accessors
    Point origin() const;
    Point direction() const;
    bool hit(Point point) const;

    Point getPoint(int length) const;
    Point getPoint(double length) const;
    Point getPoint(float length) const;

    friend std::ostream &operator<<(std::ostream &out, const Ray &ray);
};