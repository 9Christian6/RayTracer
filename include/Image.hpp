#pragma once
#include <vector>
#include <pngwriter.h>
#include "Color.hpp"
#include "Camera.hpp"
#include "Shapeset.hpp"

namespace raytracer
{
    class Image
    {
    private:
        int _width, _height;
        std::vector<bool> _pixels;

    public:
        pngwriter _image;
        Image(int width, int height);
        int width() const;
        int height() const;
        void setPixel(int x, int y, bool value);
        void plot(int x, int y, Color &color);
        bool pixel(int x, int y) const;
    };
}