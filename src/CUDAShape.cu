#include "CUDAShape.hpp"
#include "Ray.hpp"
// #include "fEquals.hpp"
#include <limits.h>

namespace raytracer
{
    __host__ __device__ bool equals(double lhs, double rhs)
    {
        return std::abs(lhs - rhs) <= __DBL_EPSILON__;
    }

    __host__ __device__ Vector3 newVector3(double x, double y, double z)
    {
        Vector3 s_vec3;
        s_vec3._x = x;
        s_vec3._y = y;
        s_vec3._z = z;
        return s_vec3;
    }

    __host__ __device__ Image newImage(int width, int height)
    {
        Image img;
        img._width = width;
        img._height = height;
        img._pixels = new Color3[width * height];
        return img;
    }

    // __host__ __device__ Vector3 Vector3_new(const Vector &vec)
    // {
    //     Vector3 s_vec3;
    //     s_vec3._x = vec.x();
    //     s_vec3._y = vec.y();
    //     s_vec3._z = vec.z();
    //     return s_vec3;
    // }

    __host__ __device__ Color3 S_Color_new(double r, double g, double b)
    {
        Color3 c;
        c._r = r;
        c._g = g;
        c._b = b;
        return c;
    }

    // __host__ __device__ Ray3 S_ray_new(const Ray &ray)
    // {
    //     Ray3 r;
    //     r._d = Vector3_new(ray.direction());
    //     r._o = Vector3_new(ray.origin());
    //     return r;
    // }

    __host__ __device__ Ray3 newRay3(Vector3 &origin, Vector3 &direction)
    {
        Ray3 r;
        r._o = origin;
        r._d = direction;
        return r;
    }

    __host__ __device__ Vector3 normalize(const Vector3 &op)
    {
        return (op * (1 / length((op))));
    }

    __host__ __device__ Camera3 newCamera(Vector3 &position, Vector3 &forward, Vector3 &up, double fov, double aspectRatio)
    {
        Camera3 cam;
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

    // __host__ __device__ Intersection3 S_intersection_new()
    // {
    //     Intersection3 intersection;
    //     intersection.hit = false;
    //     return intersection;
    // }

    __host__ __device__ Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs)
    {
        Vector3 sum;
        sum._x = lhs._x + rhs._x;
        sum._y = lhs._y + rhs._y;
        sum._z = lhs._z + rhs._z;
        return sum;
    }

    __host__ __device__ Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs)
    {
        Vector3 diff;
        diff._x = lhs._x - rhs._x;
        diff._y = lhs._y - rhs._y;
        diff._z = lhs._z - rhs._z;
        return diff;
    }

    __host__ __device__ Vector3 operator*(double scale, Vector3 &op)
    {
        Vector3 prod;
        prod._x = op._x * scale;
        prod._y = op._y * scale;
        prod._z = op._z * scale;
        return prod;
    }

    __host__ __device__ Vector3 operator*(const Vector3 &op, double scale)
    {
        Vector3 prod;
        prod._x = op._x * scale;
        prod._y = op._y * scale;
        prod._z = op._z * scale;
        return prod;
    }

    __host__ __device__ double operator*(const Vector3 &lhs, const Vector3 &rhs)
    {
        return lhs._x * rhs._x + lhs._y * rhs._y + lhs._z * rhs._z;
    }

    __host__ __device__ double length(const Vector3 &op)
    {
        return std::sqrt(op * op);
    }

    __host__ __device__ double dotPorduct(const Vector3 &lhs, const Vector3 &rhs)
    {
        return lhs._x * rhs._x + lhs._y * rhs._y + lhs._z * rhs._z;
    }

    __host__ __device__ Vector3 crossProduct(const Vector3 &lhs, const Vector3 &rhs)
    {
        double x, y, z;
        x = lhs._y * rhs._z - lhs._z * rhs._y;
        y = lhs._z * rhs._x - lhs._x * rhs._z;
        z = lhs._x * rhs._y - lhs._y * rhs._x;
        return newVector3(x, y, z);
    }

    __host__ __device__ bool orthogonal(const Vector3 &lhs, const Vector3 &rhs)
    {
        // return (dotPorduct(lhs, rhs) <= __DBL_EPSILON__);
        return raytracer::equals(dotPorduct(lhs, rhs), 0);
    }

    __host__ __device__ bool plane_contains(Plane3 plane, Vector3 point)
    {
        return orthogonal(plane._n, plane._o - point);
    }

    __host__ __device__ double lambert(const Vector3 &light, const Vector3 &position, const Vector3 &normal)
    {
        double brightness{0};
        auto lightDirection = light - position;
        lightDirection = normalize(lightDirection);
        brightness = normal * lightDirection;
        return std::abs(brightness);
    }

    // __host__ __device__ bool visible(thrust::host_vector<TaggedShape> scene, Vector3 position, Vector3 light)
    // {
    //     double t = length(position - light);
    //     auto lightDirection = normalize(position - light);
    //     auto lightRay = S_ray_new(light - 0.1 * lightDirection, lightDirection);
    //     auto firstLightHit = intersectShapes(scene, lightRay).t;
    //     return (t < firstLightHit);
    // }

    __host__ __device__ double calculateLambert(Intersection3 hit, Vector3 light)
    {
        double shade = lambert(light, hit._position, hit._normal);
        return shade;
    }

    // __host__ __device__ double calculateLambert(thrust::host_vector<TaggedShape> shapes, Intersection3 hit, thrust::host_vector<Vector3> lights)
    // {
    //     double shade{0};
    //     for (auto light : lights)
    //     {
    //         if (visible(shapes, hit._position, light))
    //             shade += lambert(light, hit._position, hit._normal);
    //     }
    //     return shade;
    // }

    __host__ __device__ Intersection3 intersectShape(TaggedShape shape, Ray3 ray)
    {
        Intersection3 intersection;
        Plane3 plane;
        Sphere3 sphere;
        double denom{0}, t{0}, B, C;
        bool contains{false};
        Vector3 sum, prod, normal;
        switch (shape._tag)
        {
        case SPHERE:
            sphere = shape._shape._sphere;
            B = ray._d._x * (ray._o._x - sphere._o._x);
            B += ray._d._y * (ray._o._y - sphere._o._y);
            B += ray._d._z * (ray._o._z - sphere._o._z);
            B *= 2;
            C = std::pow((ray._o._x - sphere._o._x), 2);
            C += std::pow((ray._o._y - sphere._o._y), 2);
            C += std::pow((ray._o._z - sphere._o._z), 2);
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
                intersection._ray = ray;
                prod = t * ray._d;
                sum = ray._o + prod;
                normal = sum - sphere._o;
                intersection.lambert = lambert(ray._o, sum, normal);
                intersection._color = shape._color;
                intersection._normal = normal;
                intersection._position = calculateRayPoint(intersection._ray, intersection.t);
                intersection._shape = SPHERE;
            }
            break;

        case PLANE:
            plane = shape._shape._plane;
            denom = dotPorduct(plane._n, ray._d);
            contains = orthogonal(plane._n, plane._o - ray._o);
            if (equals(denom, 0) && !(plane_contains(plane, ray._o)))
            {
                intersection.hit = false;
                break;
            }
            if (equals(denom, 0) && (plane_contains(plane, ray._o)))
            {
                intersection.hit = true;
                intersection._ray = ray;
                intersection.t = 1;
                intersection._normal = plane._n;
                intersection._shape = PLANE;
                break;
            }
            t = dotPorduct(plane._o - ray._o, plane._n) / denom;
            if (t > 0)
            {
                intersection.hit = true;
                intersection._ray = ray;
                intersection.t = t;
                intersection._position = calculateRayPoint(intersection._ray, t);
                prod = t * ray._d;
                sum = ray._o + prod;
                intersection.lambert = lambert(ray._o, sum, plane._n);
                intersection._normal = plane._n;
                intersection._shape = PLANE;
                break;
            }

        default:
            break;
        }
        return intersection;
    };

    // __host__ __device__ Color3 getPixel(Image img, size_t x, size_t y)
    // {
    //     int position = y * img._width + x;
    //     return img._pixels[position];
    // }

    // __host__ __device__ void setColor(Image img, size_t x, size_t y, Color3 color)
    // {
    //     int position = y * img._width + x;
    //     img._pixels[position] = color;
    // }

    // __host__ __device__ Ray3 makeRay(Camera cam, size_t width, size_t height, size_t x, size_t y)
    // {
    //     double xR = ((x / (double)width) * 2) - 1;
    //     double yR = ((y / (double)height) * 2) - 1;
    //     auto vec = cam._forward + xR * cam._w * cam._right;
    //     auto direction = cam._forward + xR * cam._w * cam._right;
    //     direction = direction + yR * cam._h * cam._up;
    //     direction = normalize(direction);
    //     return S_ray_new(cam._pos, direction);
    // }

    __host__ __device__ Vector3 calculateRayPoint(Ray3 ray, double t)
    {
        return ray._o + ray._d * t;
    }

    __host__ __device__ Intersection3 intersectShapes(CUDAScene scene, Ray3 ray)
    {
        Intersection3 hit;
        hit.hit = false;
        hit.t = __DBL_MAX__;
        for (int i = 0; i < scene.numShapes; i++)
        {
            auto temp = intersectShape(scene._shapes[i], ray);
            if (temp.t < hit.t)
                hit = temp;
        }
        return hit;
    }

    // __host__ __device__ Intersection3 intersectShapes(thrust::host_vector<TaggedShape> shapes, Ray3 ray)
    // {
    //     Intersection3 hit;
    //     hit.hit = false;
    //     hit.t = __DBL_MAX__;
    //     for (auto shape : shapes)
    //     {
    //         auto temp = intersectShape(shape, ray);
    //         if (temp.hit && temp.t < hit.t)
    //             hit = temp;
    //     }
    //     return hit;
    // }

}