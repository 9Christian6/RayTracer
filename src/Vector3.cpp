#include "Vector3.hpp"
#include "fEquals.hpp"
#include <cmath>
namespace raytracer
{

    Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs)
    {
        Vector3 sum;
        sum._x = lhs._x + rhs._x;
        sum._y = lhs._y + rhs._y;
        sum._z = lhs._z + rhs._z;
        return sum;
    }

    Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs)
    {
        Vector3 diff;
        diff._x = lhs._x - rhs._x;
        diff._y = lhs._y - rhs._y;
        diff._z = lhs._z - rhs._z;
        return diff;
    }

    Vector3 operator*(double scale, Vector3 &op)
    {
        Vector3 prod;
        prod._x = op._x * scale;
        prod._y = op._y * scale;
        prod._z = op._z * scale;
        return prod;
    }

    Vector3 operator*(const Vector3 &op, double scale)
    {
        Vector3 prod;
        prod._x = op._x * scale;
        prod._y = op._y * scale;
        prod._z = op._z * scale;
        return prod;
    }

    double operator*(const Vector3 &lhs, const Vector3 &rhs)
    {
        return lhs._x * rhs._x + lhs._y * rhs._y + lhs._z * rhs._z;
    }

    double length(const Vector3 &op)
    {
        return std::sqrt(op * op);
    }

    Vector3 normalize(const Vector3 &op)
    {
        return (op * (1 / length((op))));
    }

    double dotPorduct(const Vector3 &lhs, const Vector3 &rhs)
    {
        return lhs._x * rhs._x + lhs._y * rhs._y + lhs._z * rhs._z;
    }

    Vector3 crossProduct(const Vector3 &lhs, const Vector3 &rhs)
    {
        double x, y, z;
        x = lhs._y * rhs._z - lhs._z * rhs._y;
        y = lhs._z * rhs._x - lhs._x * rhs._z;
        z = lhs._x * rhs._y - lhs._y * rhs._x;
        return Vector3(x, y, z);
    }

    bool orthogonal(const Vector3 &lhs, const Vector3 &rhs)
    {
        return equals(dotPorduct(lhs, rhs), 0);
    }
}