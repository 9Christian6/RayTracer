#include "Vector3.hpp"
#include "fEquals.hpp"
#include <vector>
#include <optional>

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
        Ray3() = default;
    };

    struct Ray2
    {
        Vector2 _origin, _direction;
        Ray2(Vector2 origin, Vector2 direction)
        {
            _origin = origin;
            _direction = direction;
        }
        Ray2() = default;
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

    struct Polygon3
    {
        Vector3 _normal;
        std::vector<Vector3> _points;
        Polygon3() = default;
        Polygon3(Vector3 normal, std::vector<Vector3> points) : _normal(normal), _points(points) {}
    };

    struct Plane3
    {
        Vector3 _origin, _normal;
        Plane3() : _origin{}, _normal{0, 1, 0} {}
        Plane3(Vector3 origin, Vector3 normal) : _origin{origin}, _normal{normal} {}
        Plane3(Vector3 p1, Vector3 p2, Vector3 p3)
        {
            _normal = crossProduct(p1 - p2, p1 - p3);
            _origin = p1;
        }
        Plane3(Polygon3 polygon) : _normal{polygon._normal}, _origin{polygon._points.at(0)} {}
    };

    struct Line2
    {
        Vector2 _a, _b;
        Line2() = default;
        Line2(Vector2 a, Vector2 b)
        {
            _a = a;
            _b = b;
        }
    };

    enum shapeTag

    {
        SPHERE,
        PLANE,
        POLYGON
    };

    struct TaggedShape
    {
        shapeTag _tag;
        union
        {
            Sphere3 _sphere;
            Plane3 _plane;
            Polygon3 _polygon;
        };
        Color3 _color;
        TaggedShape(shapeTag tag, Sphere3 sphere, Color3 color) : _tag{tag}, _color{color}, _sphere{sphere} {}
        TaggedShape(shapeTag tag, Plane3 plane, Color3 color) : _tag{tag}, _color{color}, _plane{plane} {}
        TaggedShape(shapeTag tag, Polygon3 polygon, Color3 color) : _tag{tag}, _color{color}, _polygon{polygon} {}
        TaggedShape(const TaggedShape &taggedShape)
        {
            _tag = taggedShape._tag;
            _color = taggedShape._color;
            switch (taggedShape._tag)
            {
            case PLANE:
                _plane = taggedShape._plane;
                break;

            case SPHERE:
                _sphere = taggedShape._sphere;
                break;

            case POLYGON:
                _polygon = taggedShape._polygon;
                break;
            default:
                break;
            }
        }
        ~TaggedShape()
        {
            if (_tag == POLYGON)
                _polygon.~Polygon3();
        }
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

    void printImage(const Image &img);

    bool plane_contains(const Plane3 &plane, const Vector3 &point);

    double lambert(const Vector3 &light, const Vector3 &position, const Vector3 &normal);

    Ray3 makeRay(const Camera &cam, size_t width, size_t height, size_t x, size_t y);

    Vector3 calculateRayPoint(const Ray3 &ray, double t);

    Intersection intersectShape(const TaggedShape &shape, const Ray3 &ray);

    std::optional<Vector2> intersectLine(const Line2 &line, const Ray2 &ray);

    Intersection intersectShapes(const std::vector<TaggedShape> &shapes, const Ray3 &ray);

    double calculateLambert(const Intersection &hit, const Vector3 &light);

    double calculateLambert(const std::vector<TaggedShape> &shapes, const Intersection &hit, const std::vector<Vector3> &lights);

    std::optional<double> getT(const Ray2 &line, const Vector2 &point);

    Vector2 scale(const Ray2 &ray, double t);

    bool contains(const Line2 &line, const Vector2 &point);
#endif
    // SHAPE_H
}