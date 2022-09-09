#include <iostream>
#include <cstring>
#include <string>
#include <math.h>
#include "Exception.hpp"
#include "CUDAShape.hpp"
#include "CUDAScene.hpp"
#include "Vector3.hpp"
#include <cmath>

using namespace raytracer;
int main(int, char **)
{
    Vector3 origin{0, 0, 0}, xVec{1, 0, 0}, yVec{0, 1, 0}, zVec{0, 0, 1};
    CUDAScene parScene;
    parScene._lights.push_back(3 * zVec + 4 * yVec + 4 * xVec);
    Camera cam{Vector3(yVec), Vector3(zVec), Vector3(yVec), 10, 1};
    parScene._cam = cam;
    Plane3 xzPlane, yzPlane;
    xzPlane._normal = Vector3(yVec);
    xzPlane._origin = Vector3(origin);
    yzPlane._normal = xVec;
    yzPlane._origin = origin;
    TaggedShape txzPlane{PLANE, xzPlane, Color3{}};
    Sphere3 sphere;
    sphere._origin = Vector3(10 * zVec + yVec);
    sphere._r = 0.5;
    TaggedShape tSphere{SPHERE, sphere, Color3{}};
    Polygon3 poly;
    poly._normal = Vector3{0, 0, -1};
    poly._points.emplace_back(-1, 0, 10);
    poly._points.emplace_back(0, 1, 10);
    poly._points.emplace_back(1, 0, 10);
    TaggedShape tPoly{POLYGON, poly, Color3{}};
    // parScene._hostShapes.push_back(tSphere);
    // parScene._hostShapes.emplace_back(PLANE, xzPlane, Color3{});
    parScene._hostShapes.emplace_back(PLANE, xzPlane, Color3{});
    parScene._hostShapes.emplace_back(POLYGON, poly, Color3{});

    render(parScene, 1000, 1000);
}
