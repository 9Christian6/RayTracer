#include "Image.hpp"
#include "Shapeset.hpp"
#include "Scene.hpp"
#include "Vector.hpp"
namespace raytracer
{
#ifndef RENDERKERNEL_H
#define RENDERKERNEL_H
    Color renderPixel(int width, int height, int xResolution, int yResolution, const Scene &scene, int bounces, int samples);
    Color globalLight(Intersection &hit, const Scene &scene, int samples);
    void parTest(Vector &lhs, Vector &rhs);
    void incVec3(Vector &vec);
#endif
    // RENDERKERNEL_H
}