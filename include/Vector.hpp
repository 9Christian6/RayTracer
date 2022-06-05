#pragma once
#include "Vector2.hpp"
#include <ostream>

namespace raytracer
{
    class Vector
    {
    private:
        double _x, _y, _z;

    public:
        // constructors
        Vector() = default;
        Vector(int x, int y, int z);
        Vector(double x, double y, double z);

        // accessors
        double x() const;
        double y() const;
        double z() const;
        float x_f() const;
        float y_f() const;
        float z_f() const;

        double length() const;
        double angle(const Vector &vector) const;
        bool orthogonal(const Vector &vec) const;
        bool parallel(const Vector &vec) const;
        Vector normalize() const;
        Vector cross(const Vector &vec) const;
        Vector2 project(int dim) const;
        Vector reflect(const Vector &normal) const;

        friend Vector operator+(const Vector &lhs, const Vector &rhs);
        friend Vector operator-(const Vector &lhs, const Vector &rhs);
        friend Vector operator-(const Vector &op);
        friend double operator*(const Vector &lhs, const Vector &rhs);
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
}
