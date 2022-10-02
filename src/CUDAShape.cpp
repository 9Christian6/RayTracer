#include "CUDAShape.hpp"
#include "Vector3.hpp"
#include "SafeDivision.hpp"
#include <limits.h>
#include <string.h>
#include <numeric>
#include <fstream>
#include <optional>
#include <iostream>

namespace raytracer
{
    void printImage(const Image &img)
    {
        std::string image;
        image.append("P3\n");
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
                image.append(std::to_string((int)pixelColor._r));
                image.append(" ");
                image.append(std::to_string((int)pixelColor._g));
                image.append(" ");
                image.append(std::to_string((int)pixelColor._b));
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

    bool plane_contains(const Plane3 &plane, const Vector3 &point)
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

    bool visible(const std::vector<TaggedShape> &scene, const Vector3 &position, const Vector3 &light)
    {
        double t = length(position - light);
        auto lightDirection = normalize(position - light);
        auto lightRay = Ray3(light - 0.1 * lightDirection, lightDirection);
        auto firstLightHit = intersectShapes(scene, lightRay).t;
        return (t < firstLightHit);
    }

    double calculateLambert(const Intersection &hit, const Vector3 &light)
    {
        double shade = lambert(light, hit._position, hit._normal);
        return shade;
    }

    double calculateLambert(const std::vector<TaggedShape> &shapes, const Intersection &hit, const std::vector<Vector3> &lights)
    {
        double shade{0};
        for (auto const &light : lights)
        {
            if (visible(shapes, hit._position, light))
                shade += lambert(light, hit._position, hit._normal);
        }
        return shade;
    }

    Vector2 scale(const Ray2 &ray, double t)
    {
        return ray._origin + ray._direction * t;
    }

    std::optional<double> getT(const Ray2 &line, const Vector2 &point)
    {
        std::optional<double> t;
        if (equals(line._direction._x, 0) && equals(line._origin._x, point._x))
            return scalarQuotient(line._direction._y, point._y - line._origin._y);
        if (equals(line._direction._y, 0) && equals(point._y, line._origin._y))
            return scalarQuotient(line._direction._x, point._x - line._origin._x);
        auto t1 = scalarQuotient(line._direction._x, point._x - line._origin._x);
        auto t2 = scalarQuotient(line._direction._y, point._y - line._origin._y);
        if (t1 && t2 && (equals(*t1, *t2)))
            t = t1;
        return t;
    }

    bool contains(const Line2 &line, const Vector2 &point)
    {
        Ray2 rayLine{line._a, line._b - line._a};
        double rayLength = length(line._b - line._a);
        if (auto lambda = getT(rayLine, point))
            return (*lambda >= 0 && *lambda <= rayLength);
        return false;
    }

    std::vector<Line2> getLines(const Polygon3 &poly, int dimToLoose)
    {
        std::vector<Line2> lines;
        for (size_t i = 0; i < poly._points.size() - 1; i++)
        {
            lines.emplace_back(poly._points[i], poly._points[i + 1], dimToLoose);
        }
        lines.emplace_back(poly._points.front(), poly._points.back(), dimToLoose);
        return lines;
    }

    Intersection intersectLine(const Line2 &line, const Ray2 &ray)
    {
        Intersection hit;
        Ray2 rayLine{line._a, line._b - line._a};
        Vector2 lineVec{line._b, line._a};
        // double lineLength = length(line._b - line._a);
        if (parallel(lineVec, rayLine._direction))
        {
            std::cout << "parallel\n";
            if (auto t = getT(rayLine, ray._origin))
                if (*t >= 0)
                {
                    auto hit2 = scale(rayLine, *t);
                    hit._position = Vector3{hit2._x, hit2._y, 0};
                    hit._hit = true;
                }
        }
        if (equals(rayLine._direction._x, 0))
        {
            double t = (rayLine._origin._x - ray._origin._x) / ray._direction._x;
            auto hitPoint = scale(ray, t);
            if (contains(line, hitPoint) && t >= 0)
            {
                auto hit2 = scale(rayLine, t);
                hit._position = Vector3{hit2._x, hit2._y, 0};
                hit.t = t;
                hit._hit = true;
            }
        }
        if (!equals(rayLine._direction._x, 0))
        {
            double t = (rayLine._origin._y - ray._origin._y);
            t += (ray._origin._x * rayLine._direction._y) / rayLine._direction._x;
            t -= (rayLine._origin._x * rayLine._direction._y) / rayLine._direction._x;
            t *= rayLine._direction._x;
            t /= ray._direction._y * rayLine._direction._x - ray._direction._x * rayLine._direction._y;
            auto hitPoint = scale(ray, t);
            if (contains(line, hitPoint) && t >= 0)
            {
                // auto hit2 = scale(ray, t);
                hit._hit = true;
                hit.lambert = 1;
            }
        }
        return hit;
    }

    Intersection intersectShape(const TaggedShape &shape, const Ray3 &ray)
    {
        int intersectionCount;
        Intersection intersection{};
        Plane3 plane;
        Sphere3 sphere;
        double denom{0}, t{0}, B, C, nX, nY, nZ;
        Vector3 sum, prod, normal;
        Vector2 p0, lastPoint;
        Ray2 testRay;
        std::vector<Line2> lines;
        switch (shape._tag)
        {
        case SPHERE:
            sphere = shape._sphere;
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
            plane = shape._plane;
            denom = dotPorduct(plane._normal, ray._direction);
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
            break;
        case POLYGON:
            plane = Plane3{shape._polygon};
            intersection = intersectShape(TaggedShape{PLANE, plane, Color3{}}, ray);
            if (!intersection._hit)
                return intersection;
            intersection._hit = false;
            if (intersection.t > RAY_T_MIN)
            {
                nX = std::abs(plane._normal._x);
                nY = std::abs(plane._normal._y);
                nZ = std::abs(plane._normal._z);
                int dimToLoose;
                if (nX >= nY && nX >= nZ)
                {
                    dimToLoose = 0;
                }
                if (nY >= nX && nY >= nZ)
                {
                    dimToLoose = 1;
                }
                if (nZ >= nX && nZ >= nY)
                {
                    dimToLoose = 2;
                }
                auto hit = intersection._position;
                auto projectedHit = project(hit, dimToLoose);
                intersectionCount = 0;
                testRay = Ray2{projectedHit, Vector2{1, 0}};
                lines = getLines(shape._polygon, dimToLoose);
                for (auto line : lines)
                {
                    auto hit = intersectLine(line, testRay);
                    if (hit._hit)
                    {
                        if (!parallel(testRay._direction, (line._b - line._a)))
                            intersectionCount++;
                    }
                }
                if (intersectionCount % 2 == 1)
                {
                    intersection._hit = true;
                    intersection._shape = POLYGON;
                }
            }
            break;
        default:
            intersection._hit = false;
            break;
        }
        return intersection;
    };

    Ray3 makeRay(const Camera &cam, size_t width, size_t height, size_t x, size_t y)
    {
        double xR = ((x / (double)width) * 2) - 1;
        double yR = ((y / (double)height) * 2) - 1;
        auto direction = cam._forward + xR * cam._w * cam._right;
        direction = direction + yR * cam._h * cam._up;
        direction = normalize(direction);
        return Ray3(cam._pos, direction);
    }

    Vector3 calculateRayPoint(const Ray3 &ray, double t)
    {
        return ray._origin + ray._direction * t;
    }

    Intersection intersectShapes(const std::vector<TaggedShape> &shapes, const Ray3 &ray)
    {
        Intersection hit;
        hit._hit = false;
        hit.t = __DBL_MAX__;
        for (const auto &shape : shapes)
        {
            auto temp = intersectShape(shape, ray);
            if (temp._hit && temp.t < hit.t)
                hit = temp;
        }
        return hit;
    }

    std::ostream &operator<<(std::ostream &out, const Line2 &line)
    {
        out << "Line:\n"
            << "a: " << line._a << ", b: " << line._b << "\n";
        return out;
    }

    std::ostream &operator<<(std::ostream &out, const Ray2 &ray)
    {
        out << "Ray:\n"
            << "origin: " << ray._origin << "\n"
            << "direction: " << ray._direction << "\n";
        return out;
    }

    std::ostream &operator<<(std::ostream &out, const Vector3 &vec)
    {
        out << "Vec:\n"
            << "x: " << vec._x << "\n"
            << "y: " << vec._y << "\n"
            << "z: " << vec._z << "\n";
        return out;
    }

}