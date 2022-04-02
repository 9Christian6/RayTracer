#include "Vector.hpp"
#include <math.h>

Vector::Vector() : _x{0}, _y{0}, _z{0} {};
Vector::Vector(int x, int y, int z) : _x{(double)x}, _y{(double)y}, _z{(double)z} {};
Vector::Vector(double x, double y, double z) : _x{x}, _y{y}, _z{z} {};

double Vector::x() const
{
    return _x;
}

double Vector::y() const
{
    return _y;
}

double Vector::z() const
{
    return _z;
}

float Vector::x_f() const
{
    return (float)_x;
}

float Vector::y_f() const
{
    return (float)_y;
}

float Vector::z_f() const
{
    return (float)_z;
}

Vector operator+(const Vector &lhs, const Vector &rhs)
{
    return Vector(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z());
}

Vector operator-(const Vector &lhs, const Vector &rhs)
{
    return Vector(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
}

double operator*(const Vector &lhs, const Vector &rhs)
{
    return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
}

Vector operator*(const Vector &lhs, int length)
{
    return Vector(lhs.x() * length, lhs.y() * length, lhs.z() * length);
}

Vector operator*(const Vector &lhs, float length)
{
    return Vector(lhs.x() * length, lhs.y() * length, lhs.z() * length);
}

Vector operator*(const Vector &lhs, double length)
{
    return Vector(lhs.x() * length, lhs.y() * length, lhs.z() * length);
}

Vector operator*(int length, const Vector &lhs)
{
    return Vector(lhs.x() * length, lhs.y() * length, lhs.z() * length);
}

Vector operator*(float length, const Vector &lhs)
{
    return Vector(lhs.x() * length, lhs.y() * length, lhs.z() * length);
}

Vector operator*(double length, const Vector &lhs)
{
    return Vector(lhs.x() * length, lhs.y() * length, lhs.z() * length);
}

Vector operator/(const Vector &lhs, const Vector &rhs)
{
    return Vector(lhs.x() / rhs.x(), lhs.y() / rhs.y(), lhs.z() / rhs.z());
}

bool operator==(const Vector &lhs, const Vector &rhs)
{
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z());
}

double Vector::length() const
{
    return std::sqrt(_x * _x + _y * _y + _z * _z);
}

bool Vector::orthogonal(const Vector &vec) const
{
    return ((*this) * vec) == 0;
}

Vector Vector::normalize() const
{
    double length = std::sqrt(_x * _x + _y * _y + _z * _z);
    Vector result{*this};
    return result * (1 / length);
}

Vector Vector::cross(const Vector &vec) const
{
    double a1, a2, a3, b1, b2, b3;
    a1 = _x;
    a2 = _y;
    a3 = _z;
    b1 = vec.x();
    b2 = vec.y();
    b3 = vec.z();
    return Vector{a2 * b3 - a3 * b2, a3 * b1 - a1 * b3, a1 * b2 - a2 * b1};
}

bool Vector::parallel(const Vector &vec) const
{
    return (this->normalize() == vec.normalize());
}

std::ostream &operator<<(std::ostream &stream, Vector point)
{
    stream << "(" << point.x() << ", " << point.y() << ", " << point.z() << ")";
    return stream;
}