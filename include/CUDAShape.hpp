#include "fEquals.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include <thrust/host_vector.h>

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

    struct S_Color
    {
        double _r, _g, _b;
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
        S_Color _color;
    };

    struct S_intersection
    {
        bool hit;
        double t, lambert;
        S_vector3 _position;
        S_vector3 _normal;
        S_ray _r;
        S_Color _color;
    };

    struct S_Image
    {
        int _width, _height;
        thrust::host_vector<S_Color> _pixels;
    };

    struct S_Camera
    {
        S_vector3 _pos, _forward, _up, _right;
        double _h, _w;
    };

    S_vector3 S_vector3_new(double x, double y, double z);

    S_vector3 S_vector3_new(const Vector &vec);

    S_Color S_Color_new(double r, double g, double b);

    S_ray S_ray_new(const Ray &ray);

    S_Camera S_Camera_new(S_vector3 position, S_vector3 forward, S_vector3 up, double fov, double aspectRatio);

    S_vector3 operator+(const S_vector3 &lhs, const S_vector3 &rhs);

    S_vector3 operator-(const S_vector3 &lhs, const S_vector3 &rhs);

    S_vector3 operator*(double scale, S_vector3 &op);

    S_vector3 operator*(const S_vector3 &op, double scale);

    double operator*(const S_vector3 &lhs, const S_vector3 &rhs);

    double length(const S_vector3 &op);

    S_vector3 normalize(const S_vector3 &op);

    double dotPorduct(const S_vector3 &lhs, const S_vector3 &rhs);

    S_vector3 crossProduct(const S_vector3 &lhs, const S_vector3 &rhs);

    bool orthogonal(const S_vector3 &lhs, const S_vector3 &rhs);

    bool plane_contains(S_plane plane, S_vector3 point);

    double lambert(const S_vector3 &light, const S_vector3 &position, const S_vector3 &normal);

    S_Color getPixel(S_Image img, size_t x, size_t y);

    void setPixel(S_Image img, size_t x, size_t y, S_Color color);

    S_ray makeRay(S_Camera cam, size_t width, size_t height, size_t x, size_t y);

    S_vector3 calculateRayPoint(S_ray ray, double t);

    S_intersection intersectShape(T_shape s, S_ray r);

    S_intersection intersectShapes(thrust::host_vector<T_shape> shapes, S_ray ray);

    double calculateLambert(S_intersection hit, S_vector3 light);

    double calculateLambert(thrust::host_vector<T_shape> shapes, S_intersection hit, thrust::host_vector<S_vector3> lights);
#endif
    // SHAPE_H
}