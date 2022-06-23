#include "RenderKernel.h"
#include "Color.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "Ray2.hpp"
#include "Light.hpp"
#include <utility>
#include <random>
#include "Material.hpp"
namespace raytracer
{
    Color renderPixel(int width, int height, int x, int y, const Scene &scene, int bounces, int samples)
    {
        Color pixel{0, 0, 0};
        double reflectivity{0};
        auto ray = scene.camera().makeRay(width, height, Vector2{x, y});
        if (auto hit = scene.shapes().intersect(ray))
        {
            pixel = *hit->color(scene.visibleLights(hit->position()));
            // pixel += globalLight(*hit, scene, samples);
            ray = hit->reflectionRay();
            reflectivity = hit->material()->specularity();
        }
        for (size_t bounce = 1; bounce < bounces; bounce++)
        {
            if (auto hit = scene.shapes().intersect(ray))
            {
                pixel += *hit->color(scene.visibleLights(hit->position())) * reflectivity * (1 / std::pow(2, bounce));
                ray = hit->reflectionRay();
            }
            else
                break;
        }
        return pixel;
    }

    Color globalLight(Intersection &hit, const Scene &scene, int samples)
    {
        Color average{0, 0, 0};
        auto position{hit.position()};
        std::vector<Ray> sampleRays;
        for (int i = 0; i < samples; i++)
        {
            Vector noisyNormal = hit.normal().addNoise();
            Ray noisyRay{hit.position() + 0.1 * hit.normal(), noisyNormal};
            sampleRays.push_back(noisyRay);
        }
        for (auto ray : sampleRays)
        {
            if (auto hit = scene.shapes().intersect(ray))
            {
                double reflectivity{hit->material()->specularity()};
                double distance{hit->t()};
                average += *hit->color(scene.visibleLights(hit->position())) * std::min((reflectivity / distance), (double)1);
            }
        }
        average = average * (1 / (float)samples);
        return average;
    }

    struct vector3
    {
        int x, y, z;
    };

    __global__ void incVec(vector3 *vec)
    {
        vec->x++;
        vec->y++;
        vec->z++;
    }

    __global__ void vecAdd(double *a, double *b, double *c, int n)
    {
        int id = blockIdx.x * blockDim.x + threadIdx.x;

        if (id < n)
            c[id] = a[id] + b[id];
    }

    void incVec3(Vector &vec)
    {
        vector3 vec3;
        vec3.x = vec.x();
        vec3.y = vec.y();
        vec3.z = vec.z();
        vector3 *h_vec, *d_vec;
        size_t bytes = sizeof(vector3);
        h_vec = (vector3 *)malloc(bytes);
        cudaMalloc(&d_vec, bytes);
        h_vec->x = vec3.x;
        h_vec->y = vec3.y;
        h_vec->z = vec3.z;
        cudaMemcpy(d_vec, h_vec, bytes, cudaMemcpyHostToDevice);
        int blockSize = 1024;
        int gridSize = (int)ceil((float)3 / blockSize);
        incVec<<<gridSize, blockSize>>>(d_vec);
        cudaMemcpy(h_vec, d_vec, bytes, cudaMemcpyDeviceToHost);
        vec = Vector{h_vec->x, h_vec->y, h_vec->z};
        cudaFree(d_vec);
        free(h_vec);
    }

    void parTest(Vector &lhs, Vector &rhs)
    {
        double *h_lhs, *h_rhs, *h_result, *d_lhs, *d_rhs, *d_result;

        size_t bytes = 3 * sizeof(double);

        h_lhs = (double *)malloc(bytes);
        h_rhs = (double *)malloc(bytes);
        h_result = (double *)malloc(bytes);

        cudaMalloc(&d_lhs, bytes);
        cudaMalloc(&d_rhs, bytes);
        cudaMalloc(&d_result, bytes);

        h_lhs[0] = lhs.x();
        h_lhs[1] = lhs.y();
        h_lhs[2] = lhs.z();
        h_rhs[0] = rhs.x();
        h_rhs[1] = rhs.y();
        h_rhs[2] = rhs.z();

        cudaMemcpy(d_lhs, h_lhs, bytes, cudaMemcpyHostToDevice);
        cudaMemcpy(d_rhs, h_rhs, bytes, cudaMemcpyHostToDevice);

        int blockSize = 1024;
        int gridSize = (int)ceil((float)3 / blockSize);

        vecAdd<<<gridSize, blockSize>>>(d_lhs, d_rhs, d_result, 3);

        cudaMemcpy(h_result, d_result, bytes, cudaMemcpyDeviceToHost);

        for (int i = 0; i < 3; i++)
        {
            std::cout << h_result[i] << "\n";
        }

        cudaFree(d_lhs);
        cudaFree(d_rhs);
        cudaFree(d_result);

        free(h_lhs);
        free(h_rhs);
        free(h_result);
    }
}
