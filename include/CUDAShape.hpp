#include "Vector3.hpp"
#include "fEquals.hpp"
#include <thrust/host_vector.h>

namespace raytracer
{

#ifndef SHAPE_H
#define SHAPE_H

    static constexpr double RAY_T_MIN = 1.0e-9;
    static constexpr double RAY_T_MAX = 1.0e30;

    struct Ray3
    {
        Vector3 _origin, _direction;
        Ray3(Vector3 origin, Vector3 direction)
        {
            _origin = origin;
            _direction = direction;
        }
        Ray3()
        {
            _origin = Vector3();
            _direction = Vector3();
        }
    };

    struct Color3
    {
        double _r, _g, _b;
        Color3()
        {
            _r = 0;
            _g = 0;
            _b = 0;
        }
        Color3(double r, double g, double b)
        {
            _r = r;
            _g = g;
            _b = b;
        }
    };

    struct Sphere3
    {
        Vector3 _origin;
        double _r, _rs;
        Sphere3()
        {
            _origin = Vector3();
            _r = 1;
            _rs = 1;
        }
        Sphere3(Vector3 origin, double radius)
        {
            _origin = origin;
            _r = radius;
            _rs = _r * _r;
        }
    };

    struct Plane3
    {
        Vector3 _origin, _normal;
        Plane3()
        {
            _origin = Vector3();
            _normal = Vector3(0, 1, 0);
        }
        Plane3(Vector3 origin, Vector3 normal)
        {
            _origin = origin;
            _normal = normal;
        }
        Plane3(Vector3 p1, Vector3 p2, Vector3 p3)
        {
            _normal = crossProduct(p1 - p2, p1 - p3);
            _origin = p1;
        }
    };

    bool plane_contains(Plane3 plane, Vector3 point);

    struct Polygon3
    {
        Vector3 _normal;
        std::vector<Vector3> _points;
        ~Polygon3()
        {
            _points.~vector();
        }
    };

    enum shapeTag
    {
        SPHERE,
        PLANE,
        POLYGON
    };

    union Shape
    {
        Sphere3 _sphere;
        Plane3 _plane;
        // Polygon3 _polygon;
        Shape(Sphere3 sphere)
        {
            _sphere = sphere;
        }
        Shape(Plane3 plane)
        {
            _plane = plane;
        }
        // Shape(Polygon3 polygon)
        // {
        //     _polygon = polygon;
        // }
    };

    struct TaggedShape
    {
        shapeTag _tag;
        Shape _shape;
        Color3 _color;
        TaggedShape(shapeTag tag, Shape shape, Color3 color) : _tag{tag}, _shape{shape}, _color{color} {}
    };

    struct Intersection
    {
        bool _hit;
        double t, lambert;
        Vector3 _position;
        Vector3 _normal;
        Ray3 _ray;
        Color3 _color;
        enum shapeTag _shape;
        Intersection()
        {
            _hit = false;
        }
    };

    struct Camera
    {
        Vector3 _pos, _forward, _up, _right;
        double _h, _w;
        Camera(Vector3 position, Vector3 forward, Vector3 up, double fov, double aspectRatio)
        {
            _pos = position;
            forward = position + forward;
            up = position + up;
            _forward = normalize(forward - position);
            _right = normalize(crossProduct(_forward, up));
            _up = crossProduct(_right, _forward);
            _h = std::tan(fov);
            _w = _h * aspectRatio;
        }
        Camera() = default;
    };

    struct Image
    {
        int _width, _height;
        std::vector<std::vector<Color3>> _pixels;
        Image(size_t width, size_t height)
        {
            _width = (int)width;
            _height = (int)height;
            _pixels = std::vector<std::vector<Color3>>(_height, std::vector<Color3>(_width));
        }
        Image() = default;
    };

    void printImage(Image img);

    double lambert(const Vector3 &light, const Vector3 &position, const Vector3 &normal);

    Ray3 makeRay(Camera cam, size_t width, size_t height, size_t x, size_t y);

    Vector3 calculateRayPoint(Ray3 ray, double t);

    Intersection intersectShape(TaggedShape s, Ray3 r);

    Intersection intersectShapes(thrust::host_vector<TaggedShape> shapes, Ray3 ray);

    double calculateLambert(Intersection hit, Vector3 light);

    double calculateLambert(thrust::host_vector<TaggedShape> shapes, Intersection hit, thrust::host_vector<Vector3> lights);
#endif
    // SHAPE_H
}