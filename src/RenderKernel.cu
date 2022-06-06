#include "RenderKernel.h"
#include "Color.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "Ray2.hpp"
#include "Light.hpp"
#include <utility>
#include "Material.hpp"
namespace raytracer
{
    __global__ void renderPar()
    {
    }

    Color renderPixel(int width, int height, int x, int y, const Scene &scene, int bounces)
    {
        Color pixel{0, 0, 0};
        auto ray = scene.camera().makeRay(width, height, Vector2{x, y});
        if (auto hit = scene.shapes().intersect(ray))
        {
            pixel = *hit->color(scene.visibleLights(hit->position()));
            ray = hit->reflectionRay();
        }
        for (size_t bounce = 1; bounce < bounces; bounce++)
        {
            if (auto hit = scene.shapes().intersect(ray))
            {
                pixel += *hit->color(scene.visibleLights(hit->position())) * hit.value().material()->specularity() * (1 / (double)bounce);
                ray = hit->reflectionRay();
            }
            else
                break;
        }
        return pixel;
    }

    Color globalLight(Intersection &hit, const Scene &scene, int samples)
    {
        auto position{hit.position()};
        return Color{0, 0, 0};
    }
}