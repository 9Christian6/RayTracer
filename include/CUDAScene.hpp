#include "CUDAShape.hpp"
#include <thrust/host_vector.h>

namespace raytracer
{

#ifndef CSCENE_H
#define CSCENE_H

    struct CUDAScene
    {
        Image _img;
        Camera _cam;
        thrust::host_vector<Vector3> _lights;
        thrust::host_vector<TaggedShape> _hostShapes;
    };

    void addShape(CUDAScene scene, TaggedShape shape);

    void render(CUDAScene scene, size_t width, size_t height);

#endif
}