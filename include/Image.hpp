#pragma once
#include <vector>
#include <pngwriter.h>
#include "Color.hpp"

namespace raytracer
{
    class Image
    {
    private:
        size_t _width, _height;
        std::vector<bool> _pixels;

    public:
        pngwriter _image;
        Image() = default;
        Image(size_t width, size_t height);
        Image(std::string path);
        int width() const;
        int height() const;
        void loadImage(std::string path);
        void setPixel(int x, int y, bool value);
        void plot(int x, int y, Color &color);
        bool pixel(int x, int y) const;
    };
}