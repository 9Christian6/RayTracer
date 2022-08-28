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
                if (hit._hit)
                {
                    double lambert = calculateLambert(scene._hostShapes, hit, scene._lights);
                    lambert *= 100;
                    Color3 hitColor{lambert, lambert, lambert};
                    img._pixels[y][x] = hitColor;
                    // img.plot(x, y, hitColor);
                }
            }
        }
        printImage(img);
        // img._image.close();
    }
}