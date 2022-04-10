#include "Image.hpp"
#include "Camera.hpp"
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
                if (scene.intersect(ray))
                {
                    _pixels[y * _width + x] = true;
                    _image.plot(x, y, 1.0, 1.0, 1.0);
                }
            }
        }
        _image.close();
    }
}