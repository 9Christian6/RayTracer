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
        if (parallel(lineVec, rayLine._direction))
        {
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
                hit._hit = true;
                hit.lambert = 1;
            }
        }
        return hit;
    }

    double getB(const Ray3 &ray, const Sphere3 &sphere)
    {
        double B{ray._direction._x * (ray._origin._x - sphere._origin._x)};
        B += ray._direction._y * (ray._origin._y - sphere._origin._y);
        B += ray._direction._z * (ray._origin._z - sphere._origin._z);
        B *= 2;
        return B;
    }

    double getC(const Ray3 &ray, const Sphere3 &sphere)
    {
        double C{std::pow((ray._origin._x - sphere._origin._x), 2)};
        C += std::pow((ray._origin._y - sphere._origin._y), 2);
        C += std::pow((ray._origin._z - sphere._origin._z), 2);
        C -= std::pow(sphere._r, 2);
        return C;
    }

    Intersection intersectSphere(const Sphere3 &sphere, const Ray3 &ray)
    {
        double B{getB(ray, sphere)}, C{getC(ray, sphere)}, t{std::pow(B, 2) - (4 * C)};
        if (t > RAY_T_MIN && t < RAY_T_MAX)
        {
            t = std::sqrt(t);
            t = -B - t;
            if (t <= RAY_T_MIN)
            {
                return Intersection{};
            }
            t /= 2;
            auto position = calculateRayPoint(ray, t);
            auto normal = position - sphere._origin;
            auto shade = lambert(ray._origin, position, normal);
            return Intersection{true, t, shade, position, normal, ray, Color3{}, SPHERE};
        }
        return Intersection{};
    };

    Dimension dimToLose(double x, double y, double z)
    {
        x = std::abs(x);
        y = std::abs(y);
        z = std::abs(z);
        if (x >= y && x >= z)
        {
            return Dimension::X;
        }
        if (y >= x && y >= z)
        {
            return Dimension::Y;
        }
        if (z >= x && z >= y)
        {
            return Dimension::Z;
        }
    }

    Dimension dimToLose(const Vector3 &vec)
    {
        return dimToLose(vec._x, vec._y, vec._z);
    }

    Intersection intersectPlane(const Plane3 &plane, const Ray3 &ray)
    {
        double denom{0}, t{__DBL_MAX__};
        denom = dotPorduct(plane._normal, ray._direction);
        if (equals(denom, 0) && !(plane_contains(plane, ray._origin)))
        {
            return Intersection{};
        }
        if (equals(denom, 0) && (plane_contains(plane, ray._origin)))
        {
            return Intersection{true, 0, 0, ray._origin, plane._normal, ray, Color3{}, PLANE};
        }
        t = dotPorduct(plane._origin - ray._origin, plane._normal) / denom;
        if (t > 0)
        {
            auto position = calculateRayPoint(ray, t);
            auto prod = t * ray._direction;
            auto sum = ray._origin + prod;
            double shade = lambert(ray._origin, sum, plane._normal);
            return Intersection{true, t, shade, position, plane._normal, ray, Color3{}, PLANE};
        }
        return Intersection{};
    }

    Intersection intersectPolygon(const Polygon3 &poly, const Ray3 &ray)
    {
        auto plane = Plane3{poly};
        auto intersection = intersectPlane(plane, ray);
        if (!intersection._hit)
            return intersection;
        intersection._hit = false;
        if (intersection.t <= RAY_T_MIN)
            return intersection;
        auto dimToLoose = dimToLose(plane._normal);
        auto projectedHit = project(intersection._position, dimToLoose);
        auto testRay = Ray2{projectedHit, Vector2{1, 0}};
        auto lines = getLines(poly, dimToLoose);
        auto intersectionCount = 0;
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
        return intersection;
    }

    Intersection intersectShape(const TaggedShape &shape, const Ray3 &ray)
    {
        Intersection intersection{};
        switch (shape._tag)
        {
        case SPHERE:
            intersection = intersectSphere(shape._sphere, ray);
            break;

        case PLANE:
            intersection = intersectPlane(shape._plane, ray);
            break;
        case POLYGON:
            intersection = intersectPolygon(shape._polygon, ray);
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

    std::vector<Vector3> randomSamples(const Vector3 &position, int numSamples)
    {
        std::vector<Vector3> points;
        double phi = M_PI * (3. - sqrt(5.));
        for (int i = 0; i < numSamples; i++)
        {
            double y = 1 - (i / (float)(numSamples - 1)) * 2;
            double radius = sqrt(1 - y * y);
            double theta = phi * i;
            double x = cos(theta) * radius;
            double z = sin(theta) * radius;
            points.emplace_back(Vector3{x, y, z} - position);
        }
        return points;
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