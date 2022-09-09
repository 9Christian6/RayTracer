#include "CUDAShape.hpp"
#include <vector>

namespace raytracer
{

#ifndef CSCENE_H
#define CSCENE_H

    struct CUDAScene
    {
        Image _img;
        Camera _cam;
        std::vector<Vector3> _lights;
        std::vector<TaggedShape> _hostShapes;
    };

    void addShape(CUDAScene scene, TaggedShape shape);

    void render(CUDAScene scene, size_t width, size_t height);

#endif
}