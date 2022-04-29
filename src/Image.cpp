#include "Image.hpp"
#include "Color.hpp"
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

    void Image::plot(int x, int y, Color &color)
    {
        _image.plot(x, y, color.r(), color.g(), color.b());
    }
}