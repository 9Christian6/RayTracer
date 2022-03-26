#include "Point.hpp"

Point::Point() : _x{0}, _y{0}, _z{0} {};
Point::Point(int x, int y, int z) : _x{x}, _y{y}, _z{z} {};
Point::Point(double x, double y, double z) : _x{x}, _y{y}, _z{z} {};
// Point::Point(float x, float y, float z) : _x{x}, _y{y}, _z{z} {};
Point::Point(pfrac::PrecisionFraction x, pfrac::PrecisionFraction y, pfrac::PrecisionFraction z) : _x{x}, _y{y}, _z{z} {};

pfrac::PrecisionFraction Point::x() const
{
    return _x;
}

pfrac::PrecisionFraction Point::y() const
{
    return _y;
}

pfrac::PrecisionFraction Point::z() const
{
    return _z;
}

double Point::x_d() const
{
    return _x._fracDouble;
}

double Point::y_d() const
{
    return _y._fracDouble;
}

double Point::z_d() const
{
    return _z._fracDouble;
}

float Point::x_f() const
{
    return (float)_x._fracDouble;
}

float Point::y_f() const
{
    return (float)_y._fracDouble;
}

float Point::z_f() const
{
    return (float)_z._fracDouble;
}

Point operator+(const Point &lhs, const Point &rhs)
{
    return Point(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z());
}

Point operator-(const Point &lhs, const Point &rhs)
{
    return Point(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
}

Point operator*(const Point &lhs, const Point &rhs)
{
    return Point(lhs.x() * rhs.x(), lhs.y() * rhs.y(), lhs.z() * rhs.z());
}

Point operator*(const Point &lhs, int length)
{
    return Point(lhs.x() * length, lhs.y() * length, lhs.z() * length);
}

Point operator*(const Point &lhs, float length)
{
    return Point(lhs.x() * length, lhs.y() * length, lhs.z() * length);
}

Point operator*(const Point &lhs, double length)
{
    return Point(lhs.x() * length, lhs.y() * length, lhs.z() * length);
}

Point operator*(int length, const Point &lhs)
{
    return Point(lhs.x() * length, lhs.y() * length, lhs.z() * length);
}

Point operator*(float length, const Point &lhs)
{
    return Point(lhs.x() * length, lhs.y() * length, lhs.z() * length);
}

Point operator*(double length, const Point &lhs)
{
    return Point(lhs.x() * length, lhs.y() * length, lhs.z() * length);
}

Point operator/(const Point &lhs, const Point &rhs)
{
    return Point(lhs.x() / rhs.x(), lhs.y() / rhs.y(), lhs.z() / rhs.z());
}

bool operator==(const Point &lhs, const Point &rhs)
{
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z());
}

std::ostream &operator<<(std::ostream &stream, Point point)
{
    stream << "(" << point.x() << ", " << point.y() << ", " << point.z() << ")";
    return stream;
}