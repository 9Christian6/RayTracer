#include "RenderKernel.h"

__global__ void renderPar()
{
}

void render(const raytracer::Scene *scene)
{
    renderPar<<<1, 1>>>();
}