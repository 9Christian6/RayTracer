#pragma once
namespace raytracer
{
    struct Vector3
    {
        double _x, _y, _z;
        Vector3()
        {
            _x = 0;
            _y = 0;
            _z = 0;
        }
        Vector3(double x, double y, double z)
        {
            _x = x;
            _y = y;
            _z = z;
        }
    };

    struct Vector2
    {
        double _x, _y;
        Vector2()
        {
            _x = 0;
            _y = 0;
        }
        Vector2(double x, double y)
        {
            _x = x;
            _y = y;
        }
        Vector2(const Vector2 &a, const Vector2 &b)
        {
            _x = b._x - a._x;
            _y = b._y - a._y;
        }
    };

    Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs);

    Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs);

    Vector3 operator*(double scale, Vector3 &op);

    Vector3 operator*(const Vector3 &op, double scale);

    double operator*(const Vector3 &lhs, const Vector3 &rhs);

    double length(const Vector3 &op);

    double length(const Vector2 &op);

    Vector3 normalize(const Vector3 &op);

    double dotPorduct(const Vector3 &lhs, const Vector3 &rhs);

    Vector3 crossProduct(const Vector3 &lhs, const Vector3 &rhs);

    bool orthogonal(const Vector3 &lhs, const Vector3 &rhs);

    Vector2 project(const Vector3 &vec, int dimToLoose);

    Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs);

    Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs);

    Vector2 operator*(double scale, Vector2 &op);

    Vector2 operator*(const Vector2 &op, double scale);

    double operator*(const Vector2 &lhs, const Vector2 &rhs);

    bool operator==(const Vector2 &lhs, const Vector2 &rhs);

    double length(const Vector2 &op);

    Vector2 normalize(const Vector2 &op);

    double dotPorduct(const Vector2 &lhs, const Vector2 &rhs);

    bool orthogonal(const Vector2 &lhs, const Vector2 &rhs);

    bool parallel(const Vector2 &lhs, const Vector2 &rhs);
}