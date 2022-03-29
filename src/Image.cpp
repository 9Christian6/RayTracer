#include "Image.hpp"
#include <vector>

Image::Image(int width, int height) : _width{width}, _height{height}
{
    pixels.resize(width * height);
    std::fill(pixels.begin(), pixels.end(), false);
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
    pixels[x * _width + y] = value;
}