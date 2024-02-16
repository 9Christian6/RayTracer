#include <iostream>
#include "BoundingBox.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Shapeset.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"
#include "Vector.hpp"

using namespace raytracer;
int main(int, char **)
{
    Vector origin{0, 0, 0}, xVec{1, 0, 0}, yVec{0, 1, 0}, zVec{0, 0, 1};
    Camera camera{0.5 * yVec, zVec, yVec, 45, 1};
    Triangle triangle{{-xVec + 5 * zVec - 3 * yVec, xVec + 5 * zVec - 3 * yVec,
                       2 * yVec + 5 * zVec}};
    Triangle triangle2{{-2 * xVec + 5 * zVec - 3 * yVec, 5 * zVec - 3 * yVec,
                        -xVec + 2 * yVec + 5 * zVec}};
    auto sphere = Sphere{5 * zVec, 2};
    auto tri = Triangle{{-1, 0, -5}, {1, 0, -5}, {0, 0, 5}};
    auto test = tri.boundingBox().longestDim();
    triangle.setColor({1, 0, 1});
    triangle2.setColor({0, 1, 0});
    Plane xzPlane{origin - yVec, yVec};
    Plane yzPlane{-xVec, xVec};
    // auto shapes = ShapeSet{{&triangle, &triangle2, &xzPlane}};
    auto shapes = ShapeSet{{&triangle, &triangle2, &sphere}};
    auto light = Light{{0, 2, 0}};
    auto lights = {light};
    auto scene = Scene{lights, shapes, camera};
    scene.render(1000, 1000);
}
