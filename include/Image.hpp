#pragma once
#include <vector>
#include "Color.hpp"
#include "Camera.hpp"
#include "Shapeset.hpp"
#include <string>

namespace raytracer
{
    class Image
    {
    private:
        int m_width, m_height;
        std::vector<std::vector<Color>> m_pixels;

    public:
        Image(int width, int height);
        int width() const;
        int height() const;
        void plot(int x, int y, Color &color);
        void write(std::string path);
    };
}