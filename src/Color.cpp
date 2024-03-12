#include "Color.hpp"
#include "OBJ_Loader.h"

namespace raytracer
{

	Color::Color(float r, float g, float b) : _r{ r }, _g{ g }, _b{ b }
	{
	}

	Color::Color(objl::Vector3 Kd) : _r{Kd.X}, _g{Kd.Y}, _b{Kd.Z}{}

	float clamp(float color) {
		if (color < 0)
			color = 0;
		if (color > 1)
			color = 1;
		return color;
	}

	float Color::r() const
	{
		return _r;
	}

	float Color::g() const
	{
		return _g;
	}

	float Color::b() const
	{
		return _b;
	}

	int convertColor(float color) {
		return (int)(clamp(color) * 255);
	}

	std::string Color::getColorTriplet()const {
		std::string colorTriplet{ "" };
		colorTriplet += std::to_string(convertColor(_r)) + " ";
		colorTriplet += std::to_string(convertColor(_g)) + " ";
		colorTriplet += std::to_string(convertColor(_b)) + " ";
		return colorTriplet;
	}

	Color Color::clamp(float min, float max) const
	{
		float newR{ _r }, newG{ _g }, newB{ _b };
		if (_r < min)
			newR = min;
		if (_r > max)
			newR = max;
		if (_g < min)
			newG = min;
		if (_g > max)
			newG = max;
		if (_b < min)
			newB = min;
		if (_b > max)
			newB = max;
		return Color{ newR, newG, newB };
	}

	Color operator+(const Color& lhs, const Color& rhs)
	{
		return Color(lhs.r() + rhs.r(), lhs.g() + rhs.g(), lhs.b() + rhs.b());
	}

	Color Color::operator+=(const Color& other)
	{
		_r = _r + other.r();
		_g = _g + other.g();
		_b = _b + other.b();
		return *this;
	}

	Color operator*(const Color& lhs, const Color& rhs)
	{
		return Color(lhs.r() * rhs.r(), lhs.g() * rhs.g(), lhs.b() * rhs.b());
	}

	Color operator*(const Color& lhs, float f)
	{
		return Color(lhs.r() * f, lhs.g() * f, lhs.b() * f);
	}

	Color Color::operator*=(float f)
	{
		*this = *this * f;
		return *this;
	}

}
