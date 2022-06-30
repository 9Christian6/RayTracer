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
        int _width, _height;
        S_vector3 _cam;
        thrust::host_vector<S_vector3> _lights;
        thrust::host_vector<T_shape> _hostShapes;
    };

    void addShape(CUDAScene scene, T_shape shape);

    // void setImageDim(CUDAScene scene, int width, int height)
    // {
    //     scene._img = Image{width, height};
    // }

    // S_intersection intersectShapes(CUDAScene scene, S_ray ray)
    // {
    //     S_intersection potHit;
    //     for (int i = 0; i < sizeof(scene._shapes) / sizeof(T_shape); i++)
    //     {
    //         potHit = intersectShape(scene._shapes, ray);
    //         if (potHit.hit)
    //             return potHit;
    //     }
    //     return potHit;
    // }

#endif
}