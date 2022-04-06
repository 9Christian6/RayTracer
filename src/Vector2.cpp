#include "Vector2.hpp"
#include "math.h"
#include "fEquals.hpp"
#include <optional>

Vector2::Vector2() : _x{0}, _y{0} {};
Vector2::Vector2(int x, int y) : _x{(double)x}, _y{(double)y} {};
Vector2::Vector2(double x, double y) : _x{x}, _y{y} {};

double Vector2::x() const
{
    return _x;
}

double Vector2::y() const
{
    return _y;
}

Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs)
{
    return Vector2(lhs.x() + rhs.x(), lhs.y() + rhs.y());
}

Vector2 operator+=(Vector2 &lhs, const Vector2 &rhs)
{
    lhs = lhs + rhs;
    return lhs + rhs;
}

Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs)
{
    return Vector2(lhs.x() - rhs.x(), lhs.y() - rhs.y());
}

Vector2 operator-=(Vector2 &lhs, const Vector2 &rhs)
{
    lhs = lhs - rhs;
    return lhs - rhs;
}

Vector2 operator-(const Vector2 &vec)
{
    return -1 * vec;
}

double operator*(const Vector2 &lhs, const Vector2 &rhs)
{
    return lhs.x() * rhs.x() + lhs.y() * rhs.y();
}

Vector2 operator*(const Vector2 &lhs, int length)
{
    return Vector2(lhs.x() * length, lhs.y() * length);
}

Vector2 operator*(const Vector2 &lhs, float length)
{
    return Vector2(lhs.x() * length, lhs.y() * length);
}

Vector2 operator*(const Vector2 &lhs, double length)
{
    return Vector2(lhs.x() * length, lhs.y() * length);
}

Vector2 operator*(int length, const Vector2 &lhs)
{
    return Vector2(lhs.x() * length, lhs.y() * length);
}

Vector2 operator*(float length, const Vector2 &lhs)
{
    return Vector2(lhs.x() * length, lhs.y() * length);
}

Vector2 operator*(double length, const Vector2 &lhs)
{
    return Vector2(lhs.x() * length, lhs.y() * length);
}

Vector2 operator/(const Vector2 &lhs, const Vector2 &rhs)
{
    return Vector2(lhs.x() / rhs.x(), lhs.y() / rhs.y());
}

bool operator==(const Vector2 &lhs, const Vector2 &rhs)
{
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y());
}

bool Vector2::orthogonal(const Vector2 &vec) const
{
    return ((*this) * vec) == 0;
}

Vector2 Vector2::normalize() const
{
    double length = std::sqrt(_x * _x + _y * _y);
    Vector2 result{*this};
    return result * (1 / length);
}

bool Vector2::parallel(const Vector2 &vec) const
{
    return (this->normalize() == vec.normalize());
}

double Vector2::length() const
{
    return std::sqrt(_x * _x + _y * _y);
}

std::optional<double> scalarQuotient(double a, double b)
{
    std::optional<double> s;
    if (!raytracer::equals(a, 0))
        s.emplace(b / a);
    return s;
}

std::optional<double> Vector2::scaleToReach(const Vector2 &vec) const
{
    std::optional<double> s;
    auto scaleX = scalarQuotient(_x, vec.x()), scaleY = scalarQuotient(_y, vec.y());
    if (!scaleX && !scaleY)
        return s;
    if (!scaleX && scaleY)
        if (raytracer::equals(_x, 0) && raytracer::equals(vec.x(), 0))
            s = scaleY;
    if (scaleX && !scaleY)
        if (raytracer::equals(_y, 0) && raytracer::equals(vec.y(), 0))
            s = scaleX;
    if (scaleX && scaleY)
        if (raytracer::equals(*scaleX, *scaleY))
            s = scaleX;
    return s;
}

std::ostream &operator<<(std::ostream &stream, Vector2 point)
{
    stream << "(" << point.x() << ", " << point.y() << ")";
    return stream;
}