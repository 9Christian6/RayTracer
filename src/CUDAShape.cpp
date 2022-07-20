#include "CUDAShape.hpp"
#include <limits.h>

namespace raytracer
{
    S_vector3 S_vector3_new(double x, double y, double z)
    {
        S_vector3 s_vec3;
        s_vec3._x = x;
        s_vec3._y = y;
        s_vec3._z = z;
        return s_vec3;
    }

    S_vector3 S_vector3_new(const Vector &vec)
    {
        S_vector3 s_vec3;
        s_vec3._x = vec.x();
        s_vec3._y = vec.y();
        s_vec3._z = vec.z();
        return s_vec3;
    }

    S_Color S_Color_new(double r, double g, double b)
    {
        S_Color c;
        c._r = r;
        c._g = g;
        c._b = b;
        return c;
    }

    S_ray S_ray_new(const Ray &ray)
    {
        S_ray r;
        r._d = S_vector3_new(ray.direction());
        r._o = S_vector3_new(ray.origin());
        return r;
    }

    S_ray S_ray_new(const S_vector3 &origin, const S_vector3 &direction)
    {
        S_ray r;
        r._o = origin;
        r._d = direction;
        return r;
    }

    S_Camera S_Camera_new(S_vector3 position, S_vector3 forward, S_vector3 up, double fov, double aspectRatio)
    {
        S_Camera cam;
        cam._pos = position;
        forward = position + forward;
        up = position + up;
        cam._forward = normalize(forward - position);
        cam._right = normalize(crossProduct(cam._forward, up));
        cam._up = crossProduct(cam._right, cam._forward);
        cam._h = std::tan(fov);
        cam._w = cam._h * aspectRatio;
        return cam;
    }

    S_intersection S_intersection_new()
    {
        S_intersection intersection;
        intersection.hit = false;
        return intersection;
    }

    S_vector3 operator+(const S_vector3 &lhs, const S_vector3 &rhs)
    {
        S_vector3 sum;
        sum._x = lhs._x + rhs._x;
        sum._y = lhs._y + rhs._y;
        sum._z = lhs._z + rhs._z;
        return sum;
    }

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

    S_vector3 operator*(const S_vector3 &op, double scale)
    {
        S_vector3 prod;
        prod._x = op._x * scale;
        prod._y = op._y * scale;
        prod._z = op._z * scale;
        return prod;
    }

    double operator*(const S_vector3 &lhs, const S_vector3 &rhs)
    {
        return lhs._x * rhs._x + lhs._y * rhs._y + lhs._z * rhs._z;
    }

    double length(const S_vector3 &op)
    {
        return std::sqrt(op * op);
    }

    S_vector3 normalize(const S_vector3 &op)
    {
        return (op * (1 / length((op))));
    }

    double dotPorduct(const S_vector3 &lhs, const S_vector3 &rhs)
    {
        return lhs._x * rhs._x + lhs._y * rhs._y + lhs._z * rhs._z;
    }

    S_vector3 crossProduct(const S_vector3 &lhs, const S_vector3 &rhs)
    {
        double x, y, z;
        x = lhs._y * rhs._z - lhs._z * rhs._y;
        y = lhs._z * rhs._x - lhs._x * rhs._z;
        z = lhs._x * rhs._y - lhs._y * rhs._x;
        return S_vector3_new(x, y, z);
    }

    bool orthogonal(const S_vector3 &lhs, const S_vector3 &rhs)
    {
        return equals(dotPorduct(lhs, rhs), 0);
    }

    bool plane_contains(S_plane plane, S_vector3 point)
    {
        return orthogonal(plane._n, plane._o - point);
    }

    double lambert(const S_vector3 &light, const S_vector3 &position, const S_vector3 &normal)
    {
        double brightness{0};
        auto lightDirection = light - position;
        lightDirection = normalize(lightDirection);
        brightness = normal * lightDirection;
        return std::abs(brightness);
    }

    S_intersection intersectShape(T_shape shape, S_ray r)
    {
        S_intersection intersection = S_intersection_new();
        S_plane plane;
        S_sphere sphere;
        double denom{0}, t{0}, B, C;
        bool contains{false};
        S_vector3 sum, prod, normal;
        switch (shape._tag)
        {
        case SPHERE:
            sphere = shape._shape._sphere;
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
                if (t <= RAY_T_MIN)
                {
                    break;
                }
                t /= 2;
                intersection.hit = true;
                intersection.t = t;
                intersection._r = r;
                prod = t * r._d;
                sum = r._o + prod;
                normal = sum - sphere._o;
                intersection.lambert = lambert(r._o, sum, normal);
                intersection._color = shape._color;
                intersection._position = calculateRayPoint(intersection._r, intersection.t);
                // intersection._color = intersection._color * intersection.lambert;
            }
            break;

        case PLANE:
            plane = shape._shape._plane;
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
            if (t > 0)
            {
                intersection.hit = true;
                intersection._r = r;
                intersection.t = t;
                intersection._position = calculateRayPoint(intersection._r, t);
                prod = t * r._d;
                sum = r._o + prod;
                intersection.lambert = lambert(r._o, sum, plane._n);
                break;
            }

        default:
            break;
        }
        return intersection;
    };

    S_Color getPixel(S_Image img, size_t x, size_t y)
    {
        int position = y * img._width + x;
        return img._pixels[position];
    }

    void setColor(S_Image img, size_t x, size_t y, S_Color color)
    {
        int position = y * img._width + x;
        img._pixels[position] = color;
    }

    S_ray makeRay(S_Camera cam, size_t width, size_t height, size_t x, size_t y)
    {
        double xR = ((x / (double)width) * 2) - 1;
        double yR = ((y / (double)height) * 2) - 1;
        auto vec = cam._forward + xR * cam._w * cam._right;
        auto direction = cam._forward + xR * cam._w * cam._right;
        direction = direction + yR * cam._h * cam._up;
        direction = normalize(direction);
        return S_ray_new(cam._pos, direction);
    }

    S_vector3 calculateRayPoint(S_ray ray, double t)
    {
        return ray._o + ray._d * t;
    }

    S_intersection intersectShapes(thrust::host_vector<T_shape> shapes, S_ray ray)
    {
        S_intersection hit;
        hit.hit = false;
        hit.t = __DBL_MAX__;
        for (auto shape : shapes)
        {
            auto temp = intersectShape(shape, ray);
            if (temp.hit && temp.t < hit.t)
                hit = temp;
        }
        return hit;
    }

}