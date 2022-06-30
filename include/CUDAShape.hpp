#include "fEquals.hpp"
#include "Vector.hpp"
#include "Color.hpp"
#include "Ray.hpp"

namespace raytracer
{

#ifndef SHAPE_H
#define SHAPE_H

    static constexpr double RAY_T_MIN = 1.0e-9;
    static constexpr double RAY_T_MAX = 1.0e30;

    struct S_vector3
    {
        double _x, _y, _z;
    };

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

    enum shapeTag
    {
        SPHERE,
        PLANE
    };

    union U_shape
    {
        S_sphere _sphere;
        S_plane _plane;
    };

    struct T_shape
    {
        shapeTag _tag;
        U_shape _shape;
        Color _color;
    };

    struct S_intersection
    {
        bool hit;
        double t, lambert;
        S_vector3 _position;
        S_ray _r;
        Color _color;
    };

    S_vector3 S_vector3_new(double x, double y, double z);

    S_vector3 S_vector3_new(const Vector &vec);

    S_vector3 operator+(const S_vector3 &lhs, const S_vector3 &rhs);

    S_vector3 operator-(const S_vector3 &lhs, const S_vector3 &rhs);

    S_vector3 operator*(double scale, S_vector3 &op);

    S_vector3 operator*(S_vector3 &op, double scale);

    double operator*(S_vector3 &lhs, S_vector3 &rhs);

    double length(S_vector3 &op);

    S_vector3 normalize(S_vector3 &op);

    double dotPorduct(const S_vector3 &lhs, const S_vector3 &rhs);

    bool orthogonal(const S_vector3 &lhs, const S_vector3 &rhs);

    S_ray S_ray_new(const Ray &ray);

    bool plane_contains(S_plane plane, S_vector3 point);

    static double lambert(S_vector3 &light, S_vector3 &position, S_vector3 &normal);

    static S_intersection intersectShape(T_shape s, S_ray r);

#endif
    // SHAPE_H
}