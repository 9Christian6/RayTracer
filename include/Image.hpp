#pragma once
#include <vector>
#include <pngwriter.h>
#include "Color.hpp"

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
        Image(std::string path);
        int width() const;
        int height() const;
        void loadImage(std::string path);
        void setPixel(int x, int y, bool value);
        void plot(int x, int y, Color &color);
        bool pixel(int x, int y) const;
    };
}