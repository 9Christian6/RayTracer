#include "CUDAShape.hpp"
#include "Vector3.hpp"
#include <limits.h>
#include <string.h>
#include <numeric>
#include <fstream>

namespace raytracer
{
    void printImage(Image img)
    {
        std::string image;
        image.append("P2\n");
        auto widthStr = std::to_string(img._width);
        auto heightStr = std::to_string(img._height);
        image.append(widthStr);
        image.append(" ");
        image.append(heightStr);
        image.append("\n");
        image.append("100\n");
        for (int y = 0; y < img._height; y++)
        {
            for (int x = 0; x < img._width; x++)
            {
                auto pixelColor = img._pixels[img._height - y - 1][x];
                int r, g, b;
                r = pixelColor._r;
                g = pixelColor._g;
                b = pixelColor._b;
                image.append(std::to_string(r));
                if (x < img._width - 1)
                {
                    image.append(" ");
                }
            }
            image.append("\n");
        }
        std::ofstream output;
        output.open("image");
        output << image;
        output.close();
    }

    bool plane_contains(Plane3 plane, Vector3 point)
    {
        return orthogonal(plane._normal, plane._origin - point);
    }

    double lambert(const Vector3 &light, const Vector3 &position, const Vector3 &normal)
    {
        double brightness{0};
        auto lightDirection = light - position;
        lightDirection = normalize(lightDirection);
        brightness = normal * lightDirection;
        return std::abs(brightness);
    }

    bool visible(thrust::host_vector<TaggedShape> scene, Vector3 position, Vector3 light)
    {
        double t = length(position - light);
        auto lightDirection = normalize(position - light);
        auto lightRay = Ray3(light - 0.1 * lightDirection, lightDirection);
        auto firstLightHit = intersectShapes(scene, lightRay).t;
        return (t < firstLightHit);
    }

    double calculateLambert(Intersection hit, Vector3 light)
    {
        double shade = lambert(light, hit._position, hit._normal);
        return shade;
    }

    double calculateLambert(thrust::host_vector<TaggedShape> shapes, Intersection hit, thrust::host_vector<Vector3> lights)
    {
        double shade{0};
        for (auto light : lights)
        {
            if (visible(shapes, hit._position, light))
                shade += lambert(light, hit._position, hit._normal);
        }
        return shade;
    }

    Intersection intersectShape(TaggedShape shape, Ray3 ray)
    {
        Intersection intersection{};
        Plane3 plane;
        Sphere3 sphere;
        double denom{0}, t{0}, B, C;
        bool contains{false};
        Vector3 sum, prod, normal;
        switch (shape._tag)
        {
        case SPHERE:
            sphere = shape._shape._sphere;
            B = ray._direction._x * (ray._origin._x - sphere._origin._x);
            B += ray._direction._y * (ray._origin._y - sphere._origin._y);
            B += ray._direction._z * (ray._origin._z - sphere._origin._z);
            B *= 2;
            C = std::pow((ray._origin._x - sphere._origin._x), 2);
            C += std::pow((ray._origin._y - sphere._origin._y), 2);
            C += std::pow((ray._origin._z - sphere._origin._z), 2);
            C -= std::pow(sphere._r, 2);
            t = std::pow(B, 2) - (4 * C);
            if (t > RAY_T_MIN && t < RAY_T_MAX)
            {
                t = std::sqrt(t);
                t = -B - t;
                if (t <= RAY_T_MIN)
                {
                    break;
                }
                t /= 2;
                intersection._hit = true;
                intersection.t = t;
                intersection._ray = ray;
                prod = t * ray._direction;
                sum = ray._origin + prod;
                normal = sum - sphere._origin;
                intersection.lambert = lambert(ray._origin, sum, normal);
                intersection._color = shape._color;
                intersection._normal = normal;
                intersection._position = calculateRayPoint(intersection._ray, intersection.t);
                intersection._shape = SPHERE;
            }
            break;

        case PLANE:
            plane = shape._shape._plane;
            denom = dotPorduct(plane._normal, ray._direction);
            contains = orthogonal(plane._normal, plane._origin - ray._origin);
            if (equals(denom, 0) && !(plane_contains(plane, ray._origin)))
            {
                intersection._hit = false;
                break;
            }
            if (equals(denom, 0) && (plane_contains(plane, ray._origin)))
            {
                intersection._hit = true;
                intersection._ray = ray;
                intersection.t = 1;
                intersection._normal = plane._normal;
                intersection._shape = PLANE;
                break;
            }
            t = dotPorduct(plane._origin - ray._origin, plane._normal) / denom;
            if (t > 0)
            {
                intersection._hit = true;
                intersection._ray = ray;
                intersection.t = t;
                intersection._position = calculateRayPoint(intersection._ray, t);
                prod = t * ray._direction;
                sum = ray._origin + prod;
                intersection.lambert = lambert(ray._origin, sum, plane._normal);
                intersection._normal = plane._normal;
                intersection._shape = PLANE;
                break;
            }

        // case POLYGON:
        //     plane = shape._shape._plane;
        //     denom = dotPorduct(plane._n, ray._direction);
        //     contains = orthogonal(plane._n, plane._origin - ray._origin);
        //     if (equals(denom, 0) && !(plane_contains(plane, ray._origin)))
        //     {
        //         intersection._hit = false;
        //         break;
        //     }
        //     if (equals(denom, 0) && (plane_contains(plane, ray._origin)))
        //     {
        //         intersection._hit = true;
        //         intersection._ray = ray;
        //         intersection.t = 1;
        //         intersection._normal = plane._n;
        //         intersection._shape = PLANE;
        //         break;
        //     }
        //     t = dotPorduct(plane._origin - ray._origin, plane._n) / denom;
        //     if (t > 0)
        //     {
        //         intersection._hit = true;
        //         intersection._ray = ray;
        //         intersection.t = t;
        //         intersection._position = calculateRayPoint(intersection._ray, t);
        //         prod = t * ray._direction;
        //         sum = ray._origin + prod;
        //         intersection.lambert = lambert(ray._origin, sum, plane._n);
        //         intersection._normal = plane._n;
        //         intersection._shape = PLANE;
        //         break;
        //     }
        default:
            break;
        }
        return intersection;
    };

    Ray3 makeRay(Camera cam, size_t width, size_t height, size_t x, size_t y)
    {
        double xR = ((x / (double)width) * 2) - 1;
        double yR = ((y / (double)height) * 2) - 1;
        auto vec = cam._forward + xR * cam._w * cam._right;
        auto direction = cam._forward + xR * cam._w * cam._right;
        direction = direction + yR * cam._h * cam._up;
        direction = normalize(direction);
        return Ray3(cam._pos, direction);
    }

    Vector3 calculateRayPoint(Ray3 ray, double t)
    {
        return ray._origin + ray._direction * t;
    }

    Intersection intersectShapes(thrust::host_vector<TaggedShape> shapes, Ray3 ray)
    {
        Intersection hit;
        hit._hit = false;
        hit.t = __DBL_MAX__;
        for (auto shape : shapes)
        {
            auto temp = intersectShape(shape, ray);
            if (temp._hit && temp.t < hit.t)
                hit = temp;
        }
        return hit;
    }

}