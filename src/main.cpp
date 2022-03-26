#include <iostream>
#include <gmpxx.h>
#include <Eigen/Core>
#include "Ray.hpp"
#include "Point.hpp"
#include "Exception.hpp"

int main(int, char **)
{
    Point point0{0, 0, 0};
    Point point1{1, 0, 0};
    Point point2{0, 1, 0};
    Point point3{0, 0, 1};
    Point point4{0, 1, 1};
    Point point5{1, 0, 1};
    Point point6{1, 1, 0};
    Point point7{1, 1, 1};
    Ray ray{point0, point1};
    // std::cout << ray.hit(Point{0, 0, 0}) << "\n";
    std::cout << (point0.x() != 0) << "\n";
}
