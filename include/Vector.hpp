#pragma once
#include <ostream>
#include "PrecisionFraction.hpp"

class Vector
{
private:
    pfrac::PrecisionFraction _x, _y, _z;

public:
    // constructors
    Vector();
    Vector(int x, int y, int z);
    Vector(double x, double y, double z);
    Vector(pfrac::PrecisionFraction x, pfrac::PrecisionFraction y, pfrac::PrecisionFraction z);

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

    bool parallel(const Vector &vec) const;

    friend Vector operator+(const Vector &lhs, const Vector &rhs);
    friend Vector operator-(const Vector &lhs, const Vector &rhs);
    friend pfrac::PrecisionFraction operator*(const Vector &lhs, const Vector &rhs);
    friend Vector operator*(const Vector &lhs, int length);
    friend Vector operator*(const Vector &lhs, float length);
    friend Vector operator*(const Vector &lhs, double length);
    friend Vector operator*(int length, const Vector &lhs);
    friend Vector operator*(float length, const Vector &lhs);
    friend Vector operator*(double length, const Vector &lhs);
    friend Vector operator/(const Vector &lhs, const Vector &rhs);
    friend bool operator==(const Vector &lhs, const Vector &rhs);
    friend std::ostream &operator<<(std::ostream &out, const Vector point);
};
