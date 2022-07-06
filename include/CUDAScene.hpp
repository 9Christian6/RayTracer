#include "CUDAShape.hpp"
#include "Camera.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include "Vector2.hpp"
#include <thrust/host_vector.h>

namespace raytracer
{

#ifndef CSCENE_H
#define CSCENE_H

    struct CUDAScene
    {
        S_Image _img;
        S_Camera _cam;
        thrust::host_vector<S_vector3> _lights;
        thrust::host_vector<T_shape> _hostShapes;
    };

    void addShape(CUDAScene scene, T_shape shape);

    void render(CUDAScene scene, size_t width, size_t height);

#endif
}