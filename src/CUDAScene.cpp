#include "CUDAShape.hpp"
#include "CUDAScene.hpp"
namespace raytracer
{
    void addShape(CUDAScene scene, T_shape shape)
    {
        scene._hostShapes.push_back(shape);
    }
}