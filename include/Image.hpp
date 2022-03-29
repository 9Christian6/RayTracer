#pragma once
#include <vector>

class Image
{
private:
    int _width, _height;
    std::vector<bool> pixels;

public:
    Image(int width, int height);
    int width() const;
    int height() const;
    void setPixel(int x, int y, bool value);
    bool pixel(int x, int y) const;
};