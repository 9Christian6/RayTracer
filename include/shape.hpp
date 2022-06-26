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

    double length(S_vector3 &op)
    {
        return std::sqrt(op._x * op._x + op._y * op._y + op._z * op._z);
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
        S_ray _r;
        double t;
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

    S_intersection intersect(T_shape s, S_ray r)
    {
        S_intersection intersection;
        S_plane plane;
        S_sphere sphere;
        double denom{0}, t{0};
        bool contains{false};
        switch (s.tag)
        {
        case SPHERE:
            intersection.t = 0;
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