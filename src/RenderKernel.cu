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
    __global__ void renderPar()
    {
    }

    Color renderPixel(int width, int height, int x, int y, const Scene &scene, int bounces, int samples)
    {
        Color pixel{0, 0, 0};
        double reflectivity{0};
        auto ray = scene.camera().makeRay(width, height, Vector2{x, y});
        if (auto hit = scene.shapes().intersect(ray))
        {
            pixel = *hit->color(scene.visibleLights(hit->position()));
            //pixel += globalLight(*hit, scene, samples);
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
}
