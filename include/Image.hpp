#pragma once
#include <vector>
#include <pngwriter.h>
#include "Camera.hpp"
#include "Shapeset.hpp"

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
    bool pixel(int x, int y) const;
    void print(Camera &cam, ShapeSet &scene);
};