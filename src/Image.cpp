#include "Image.hpp"
#include <iostream>
#include <vector>

namespace raytracer
{
    Image::Image(int width, int height) : _width{width}, _height{height}
    {
        _pixels.resize(width * height);
        std::fill(_pixels.begin(), _pixels.end(), false);
        _image = pngwriter(_width, _height, 0, "Image.png");
    }

    int Image::width() const
    {
        return _width;
    }

    int Image::height() const
    {
        return _height;
    }

    void Image::setPixel(int x, int y, bool value)
    {
        _pixels[x * _width + y] = value;
    }

    void Image::print(Camera &cam, ShapeSet &scene)
    {
        for (int y = 0; y < _height; y++)
        {
            for (int x = 0; x < _width; x++)
            {
                auto ray = cam.makeRay(_width, _height, Vector2{x, y});
                if (auto intersection = scene.intersect(ray))
                {
                    auto hitPosition = intersection->position();
                    if (!scene.visibleLights(hitPosition).empty())
                    {
                        _pixels[y * _width + x] = true;
                        double angle = intersection.value().angle();
                        double color = angle / 180.;
                        _image.plot(x, y, color, color, color);
                    }
                }
            }
        }
        _image.close();
    }
}