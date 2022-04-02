#pragma once
#include "Vector.hpp"
#include <vector>

class Polygon
{
private:
    std::vector<Vector> _points;

public:
    Polygon() = delete;
    Polygon(std::vector<Vector> points);
};