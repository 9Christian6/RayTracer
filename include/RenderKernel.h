#include "Image.hpp"
#include "Shapeset.hpp"
#include "Scene.hpp"
namespace raytracer
{
#ifndef RENDERKERNEL_H
#define RENDERKERNEL_H
    Color renderPixel(int width, int height, int xResolution, int yResolution, const Scene &scene, int bounces);
    Color globalLight(Intersection &hit, const Scene &scene, int samples);
#endif // RENDERKERNEL_H
}