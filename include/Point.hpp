#pragma once
#include <ostream>
#include "PrecisionFraction.hpp"

class Point
{
private:
    pfrac::PrecisionFraction _x, _y, _z;

public:
    // constructors
    Point();
    Point(int x, int y, int z);
    Point(double x, double y, double z);
    // Point(float x, float y, float z);
    Point(pfrac::PrecisionFraction x, pfrac::PrecisionFraction y, pfrac::PrecisionFraction z);

    // accessors
    pfrac::PrecisionFraction x() const;
    pfrac::PrecisionFraction y() const;
    pfrac::PrecisionFraction z() const;
    double x_d() const;
    double y_d() const;
    double z_d() const;
    float x_f() const;
    float y_f() const;
    float z_f() const;

    friend Point operator+(const Point &lhs, const Point &rhs);
    friend Point operator-(const Point &lhs, const Point &rhs);

    friend Point operator*(const Point &lhs, const Point &rhs);
    friend Point operator*(const Point &lhs, int length);
    friend Point operator*(const Point &lhs, float length);
    friend Point operator*(const Point &lhs, double length);
    friend Point operator*(int length, const Point &lhs);
    friend Point operator*(float length, const Point &lhs);
    friend Point operator*(double length, const Point &lhs);

    friend Point operator/(const Point &lhs, const Point &rhs);
    friend bool operator==(const Point &lhs, const Point &rhs);
    friend std::ostream &operator<<(std::ostream &out, const Point point);
};
