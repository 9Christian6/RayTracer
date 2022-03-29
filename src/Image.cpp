#include "Image.hpp"
#include <vector>

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

void Image::print()
{
    for (int x = 0; x < _width; x++)
    {
        for (int y = 0; y < _height; y++)
        {
            if (_pixels[x * _width + y])
                _image.plot(x, y, 1.0, 1.0, 1.0);
        }
    }
    _image.close();
}