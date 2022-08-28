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

    Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs);

    Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs);

    Vector3 operator*(double scale, Vector3 &op);

    Vector3 operator*(const Vector3 &op, double scale);

    double operator*(const Vector3 &lhs, const Vector3 &rhs);

    double length(const Vector3 &op);

    Vector3 normalize(const Vector3 &op);

    double dotPorduct(const Vector3 &lhs, const Vector3 &rhs);

    Vector3 crossProduct(const Vector3 &lhs, const Vector3 &rhs);

    bool orthogonal(const Vector3 &lhs, const Vector3 &rhs);
}