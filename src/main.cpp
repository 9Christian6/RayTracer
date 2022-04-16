#include <iostream>
#include "Ray.hpp"
#include "Vector.hpp"
#include "Exception.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "Image.hpp"
#include "Intersection.hpp"
#include "Shapeset.hpp"
#include "Polygon.hpp"
#include "Ray2.hpp"
#include "Line2.hpp"
#include <cmath>

using namespace raytracer;
int main(int, char **)
{
    Vector origin{0, 0, 0}, xVec{1, 0, 0}, yVec{0, 1, 0}, zVec{0, 0, 1};
    Vector2 origin2{0, 0}, xVec2{1, 0}, yVec2{0, 1};
    //
    //
    //
    Camera camera{yVec, zVec + yVec, 2 * yVec, 45, 1};
    Image image{1000, 1000};
    ShapeSet scene{};
    //
    //
    //
    Polygon trianlge{{-xVec - yVec + 5 * zVec, xVec - yVec + 5 * zVec, yVec + 5 * zVec}};
    Polygon square1{{Vector{-1, -1, 6}, Vector{-1, 1, 5}, Vector{1, 1, 5}, Vector{1, -1, 6}}};
    Polygon square2{{Vector{-1, -1, 5}, Vector{-1, 1, 6}, Vector{1, 1, 6}, Vector{1, -1, 5}}};
    Sphere sphere{5 * zVec, 1};
    Plane xzPlane{origin, yVec};
    Plane yzPlane{-xVec, xVec};
    //
    //
    //
    // scene.addShape(square2);
    // scene.addShape(square1);
    // scene.addShape(trianlge);
    scene.addShape(sphere);
    // scene.addShape(xyPlane);
    scene.addShape(xzPlane);
    scene.addShape(yzPlane);
    //
    //
    //
    image.print(camera, scene);
}