#include "Image.hpp"
#include "Color.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace raytracer
{
	Image::Image(int width, int height) : m_width{ width }, m_height{ height }
	{
		m_pixels = std::vector<std::vector<Color>>(m_height);
		for (int i = 0; i < m_height; ++i)
			m_pixels[i].resize(m_width);
	}

	int Image::width() const
	{
		return m_width;
	}

	int Image::height() const
	{
		return m_height;
	}

	void Image::plot(int x, int y, Color& color)
	{
		m_pixels[x][y] = color;
	}

	void Image::write(std::string path) {
		std::ofstream imgGen;
		imgGen.open(path + "Image");
		std::cout << path + "Image" << "\n";
		imgGen << "P3 \n";
		imgGen << m_width << " " << m_height << "\n";
		imgGen << 255 << "\n";

		for (int imageRow = m_height - 1; imageRow >= 0; --imageRow) {
			for (int imageColumn = 0; imageColumn < m_width; ++imageColumn){
				auto colorTriplet = m_pixels[imageColumn][imageRow].getColorTriplet();
				imgGen << colorTriplet;
			}
			imgGen << std::endl;
		}
		imgGen.close();
	}
}
