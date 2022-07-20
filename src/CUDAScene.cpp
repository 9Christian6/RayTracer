#include "CUDAShape.hpp"
#include "CUDAScene.hpp"
#include "Image.hpp"
namespace raytracer
{
    void addShape(CUDAScene scene, T_shape shape)
    {
        scene._hostShapes.push_back(shape);
    }

    void render(CUDAScene scene, size_t width, size_t height)
    {
        Image img{width, height};
        for (size_t x = 0; x < width; x++)
        {
            for (size_t y = 0; y < height; y++)
            {
                auto ray = makeRay(scene._cam, width, height, x, y);
                auto hit = intersectShapes(scene._hostShapes, ray);
                if (hit.hit)
                {
                    Color hitColor{hit.lambert, hit.lambert, hit.lambert};
                    img.plot(x, y, hitColor);
                }
            }
        }
        img._image.close();
    }
}