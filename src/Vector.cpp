#include "Vector.hpp"

Vector::Vector() : _x{0}, _y{0}, _z{0} {};
Vector::Vector(int x, int y, int z) : _x{x}, _y{y}, _z{z} {};
Vector::Vector(double x, double y, double z) : _x{x}, _y{y}, _z{z} {};
Vector::Vector(pfrac::PrecisionFraction x, pfrac::PrecisionFraction y, pfrac::PrecisionFraction z) : _x{x}, _y{y}, _z{z} {};

pfrac::PrecisionFraction Vector::x() const
{
    return _x;
}

pfrac::PrecisionFraction Vector::y() const
{
    return _y;
}

pfrac::PrecisionFraction Vector::z() const
{
    return _z;
}

double Vector::x_d() const
{
    return _x._fracDouble;
}

double Vector::y_d() const
{
    return _y._fracDouble;
}

double Vector::z_d() const
{
    return _z._fracDouble;
}

float Vector::x_f() const
{
    return (float)_x._fracDouble;
}

float Vector::y_f() const
{
    return (float)_y._fracDouble;
}

float Vector::z_f() const
{
    return (float)_z._fracDouble;
}

Vector operator+(const Vector &lhs, const Vector &rhs)
{
    return Vector(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z());
}

Vector operator-(const Vector &lhs, const Vector &rhs)
{
    return Vector(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
}

pfrac::PrecisionFraction operator*(const Vector &lhs, const Vector &rhs)
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

Vector operator*(pfrac::PrecisionFraction length, const Vector &rhs)
{
    return Vector(rhs.x() * length, rhs.y() * length, rhs.z() * length);
}

Vector operator*(const Vector &lhs, pfrac::PrecisionFraction length)
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

bool Vector::orthogonal(const Vector &vec) const
{
    return ((*this) * vec) == 0;
}

Vector Vector::normalize() const
{
    pfrac::PrecisionFraction length = pfrac::sqrt(_x * _x + _y * _y + _z * _z);
    Vector result{*this};
    return result * (1 / length.approxRealValue());
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