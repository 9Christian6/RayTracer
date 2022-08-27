#include "CUDAShape.hpp"
#include "CUDAScene.hpp"
namespace raytracer
{
    void addShape(CUDAScene scene, TaggedShape shape)
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
                    double lambert = calculateLambert(scene._hostShapes, hit, scene._lights);
                    Color3 hitColor{lambert, lambert, lambert};
                    // img.plot(x, y, hitColor);
                }
            }
        }
        // img._image.close();
    }
}