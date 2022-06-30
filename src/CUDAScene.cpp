#include "CUDAShape.hpp"
#include "CUDAScene.hpp"
namespace raytracer
{
    void addShape(CUDAScene scene, T_shape shape)
    {
        scene._hostShapes.push_back(shape);
    }

    void render(size_t x, size_t y)
    {
        for (size_t i = 0; i < x; i++)
        {
            for (size_t j = 0; j < y; j++)
            {
                // create ray
                // intersect scene with ray
                // enter color
            }
        }
        // plot picture
    }
}