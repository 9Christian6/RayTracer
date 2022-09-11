#include "Vector3.hpp"
#include "fEquals.hpp"
#include <cmath>
#include <stdexcept>
#include <ostream>
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

    Vector3 operator*(double scale, const Vector3 &op)
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

    double length(const Vector2 &op)
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

    Vector2 project(const Vector3 &vec, int dimToLoose)
    {
        switch (dimToLoose)
        {
        case 0:
            return Vector2{vec._y, vec._x};
            break;

        case 1:
            return Vector2{vec._x, vec._z};
            break;

        case 2:
            return Vector2{vec._y, vec._z};
            break;

        default:
            break;
        }
        throw std::runtime_error("Projection failed");
    }

    bool parallel(const Vector2 &lhs, const Vector2 &rhs)
    {
        return (normalize(lhs) == normalize(rhs));
    }

    Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs)
    {
        Vector2 sum;
        sum._x = lhs._x + rhs._x;
        sum._y = lhs._y + rhs._y;
        return sum;
    }

    Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs)
    {
        Vector2 diff;
        diff._x = lhs._x - rhs._x;
        diff._y = lhs._y - rhs._y;
        return diff;
    }

    Vector2 operator*(double scale, Vector2 &op)
    {
        Vector2 prod;
        prod._x = op._x * scale;
        prod._y = op._y * scale;
        return prod;
    }

    Vector2 operator*(const Vector2 &op, double scale)
    {
        Vector2 prod;
        prod._x = op._x * scale;
        prod._y = op._y * scale;
        return prod;
    }

    double operator*(const Vector2 &lhs, const Vector2 &rhs)
    {
        return lhs._x * rhs._x + lhs._y * rhs._y;
    }

    bool operator==(const Vector2 &lhs, const Vector2 &rhs)
    {
        return (equals(lhs._x, rhs._x) && equals(lhs._y, rhs._y));
    }

    Vector2 normalize(const Vector2 &op)
    {
        return (op * (1 / length((op))));
    }

    double dotPorduct(const Vector2 &lhs, const Vector2 &rhs)
    {
        return lhs._x * rhs._x + lhs._y * rhs._y;
    }

    bool orthogonal(const Vector2 &lhs, const Vector2 &rhs)
    {
        return equals(dotPorduct(lhs, rhs), 0);
    }

    std::ostream &operator<<(std::ostream &stream, const Vector2 &point)
    {
        stream << "(" << point._x << ", " << point._y << ")";
        return stream;
    }

}