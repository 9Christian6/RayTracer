#pragma once
#include <ostream>
#include <optional>

namespace raytracer
{
    class Vector2
    {
    private:
        double _x, _y;

    public:
        Vector2();
        Vector2(int x, int y);
        Vector2(double x, double y);

        bool orthogonal(const Vector2 &vec) const;
        bool parallel(const Vector2 &vec) const;
        Vector2 normalize() const;
        double length() const;
        std::optional<double> scaleToReach(const Vector2 &vec) const;

        double x() const;
        double y() const;
        friend Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs);
        friend Vector2 operator+=(Vector2 &lhs, const Vector2 &rhs);
        friend Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs);
        friend Vector2 operator-=(Vector2 &lhs, const Vector2 &rhs);
        friend Vector2 operator-(const Vector2 &vec);
        friend double operator*(const Vector2 &lhs, const Vector2 &rhs);
        friend Vector2 operator*(const Vector2 &lhs, int length);
        friend Vector2 operator*(const Vector2 &lhs, float length);
        friend Vector2 operator*(const Vector2 &lhs, double length);
        friend Vector2 operator*(int length, const Vector2 &lhs);
        friend Vector2 operator*(float length, const Vector2 &lhs);
        friend Vector2 operator*(double length, const Vector2 &lhs);
        friend Vector2 operator/(const Vector2 &lhs, const Vector2 &rhs);
        friend bool operator==(const Vector2 &lhs, const Vector2 &rhs);
        friend std::ostream &operator<<(std::ostream &out, const Vector2 point);
    };
}