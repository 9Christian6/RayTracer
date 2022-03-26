#include <iostream>
#include <gmpxx.h>
#include <Eigen/Core>
#include "Ray.hpp"
#include "Vector.hpp"
#include "Exception.hpp"

int main(int, char **)
{
    Vector point0{0, 0, 0};
    Vector point1{1, 0, 0};
    Vector point2{0, 1, 0};
    Vector point3{0, 0, 1};
    Vector point4{0, 1, 1};
    Vector point5{1, 0, 1};
    Vector point6{1, 1, 0};
    Vector point7{1, 1, 1};
    Ray ray{point0, point1};
    std::cout << (point0.x() == 0) << "\n"
              << (point0.x() != 0) << "\n";
}
