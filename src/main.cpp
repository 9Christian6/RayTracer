#include <iostream>
#include <gmpxx.h>
#include <Eigen/Core>
#include "Ray.hpp"
#include "Vector.hpp"
#include "Plane.hpp"
#include "Exception.hpp"
#include "Sphere.hpp"
#include <cmath>

int main(int, char **)
{
    std::cout.setf(std::ios::boolalpha);
    Vector origin{0, 0, 0}, xVec{1, 0, 0}, yVec{0, 1, 0}, zVec{0, 0, 1};
    Ray xRay{origin, xVec};
    Plane xzPlane{origin, yVec};
    Sphere sphere{origin, 1};
    Ray testRay{origin, xVec + yVec};
    std::cout << testRay.hit(sphere).value() << "\n";
}
