#include "fEquals.hpp"

namespace raytracer
{

#ifndef SHAPE_H
#define SHAPE_H

    enum shapeTag
    {
        SPHERE,
        PLANE
    };

    struct S_vector3
    {
        double _x, _y, _z;
    };

    S_vector3 operator-(const S_vector3 &lhs, const S_vector3 &rhs)
    {
        S_vector3 diff;
        diff._x = lhs._x - rhs._x;
        diff._y = lhs._y - rhs._y;
        diff._z = lhs._z - rhs._z;
        return diff;
    }

    S_vector3 operator*(double scale, S_vector3 &op)
    {
        S_vector3 prod;
        prod._x = op._x * scale;
        prod._y = op._y * scale;
        prod._z = op._z * scale;
        return prod;
    }

    S_vector3 operator*(S_vector3 &op, double scale)
    {
        S_vector3 prod;
        prod._x = op._x * scale;
        prod._y = op._y * scale;
        prod._z = op._z * scale;
        return prod;
    }

    double operator*(S_vector3 &lhs, S_vector3 &rhs)
    {
        return lhs._x * rhs._x + lhs._y * rhs._y + lhs._z * rhs._z;
    }

    double length(S_vector3 &op)
    {
        return std::sqrt(op * op);
    }

    S_vector3 normalize(S_vector3 &op)
    {
        return (op * (1 / length((op))));
    }

    double dotPorduct(const S_vector3 &lhs, const S_vector3 &rhs)
    {
        return lhs._x * rhs._x + lhs._y * rhs._y + lhs._z * rhs._z;
    }

    bool orthogonal(const S_vector3 &lhs, const S_vector3 &rhs)
    {
        return equals(dotPorduct(lhs, rhs), 0);
    }

    struct S_ray
    {
        S_vector3 _o, _d;
    };

    static constexpr double RAY_T_MIN = 1.0e-9;
    static constexpr double RAY_T_MAX = 1.0e30;

    struct S_sphere
    {
        S_vector3 _o;
        double _r, _rs;
    };

    struct S_plane
    {
        S_vector3 _o, _n;
    };

    bool plane_contains(S_plane plane, S_vector3 point)
    {
        return orthogonal(plane._n, plane._o - point);
    }

    struct S_intersection
    {
        bool hit;
        S_vector3 position;
        S_ray _r;
        double t, lambert;
    };

    union U_shape
    {
        S_sphere _sphere;
        S_plane _plane;
    };

    struct T_shape
    {
        shapeTag tag;
        U_shape shape;
    };

    double lambert(S_vector3 &light, S_vector3 &position, S_vector3 &normal)
    {
        double brightness{0};
        auto lightDirection = light - position;
        lightDirection = normalize(lightDirection);
        brightness = normal * lightDirection;
        return std::abs(brightness);
    }

    S_intersection intersect(T_shape s, S_ray r)
    {
        S_intersection intersection;
        S_plane plane;
        S_sphere sphere;
        double denom{0}, t{0}, B, C;
        bool contains{false};
        switch (s.tag)
        {
        case SPHERE:
            sphere = s.shape._sphere;
            B = r._d._x * (r._o._x - sphere._o._x);
            B += r._d._y * (r._o._y - sphere._o._y);
            B += r._d._z * (r._o._z - sphere._o._z);
            B *= 2;
            C = std::pow((r._o._x - sphere._o._x), 2);
            C += std::pow((r._o._y - sphere._o._y), 2);
            C += std::pow((r._o._z - sphere._o._z), 2);
            C -= std::pow(sphere._r, 2);
            t = std::pow(B, 2) - (4 * C);
            if (t > RAY_T_MIN && t < RAY_T_MAX)
            {
                t = std::sqrt(t);
                t = -B - t;
                if (t <= 0)
                {
                    intersection.hit = false;
                    break;
                }
                t /= 2;
                intersection.hit = true;
                intersection.t = t;
                intersection._r = r;
            }
            break;

        case PLANE:
            plane = s.shape._plane;
            denom = dotPorduct(plane._n, r._d);
            contains = orthogonal(plane._n, plane._o - r._o);
            if (equals(denom, 0) && !(plane_contains(plane, r._o)))
            {
                intersection.hit = false;
                break;
            }
            if (equals(denom, 0) && (plane_contains(plane, r._o)))
            {
                intersection.hit = true;
                intersection._r = r;
                intersection.t = 1;
                break;
            }
            t = dotPorduct(plane._o - r._o, plane._n) / denom;
            intersection.hit = true;
            intersection._r = r;
            intersection.t = t;
            break;

        default:
            break;
        }
        return intersection;
    };

#endif
    // SHAPE_H
}