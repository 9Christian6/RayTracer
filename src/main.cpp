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
    Vector2 origin2{0, 0}, xVec2{1, 0}, yVec2{0, 1};
    CUDAScene parScene;
    parScene._lights.push_back(3 * zVec + 4 * yVec + 4 * xVec);
    Camera cam{Vector3(yVec), Vector3(zVec), Vector3(yVec), 10, 1};
    parScene._cam = cam;
    Plane3 xzPlane, yzPlane;
    xzPlane._normal = Vector3(yVec);
    xzPlane._origin = Vector3(origin);
    yzPlane._normal = xVec;
    yzPlane._origin = origin;
    Sphere3 sphere;
    sphere._origin = Vector3(3 * zVec + yVec);
    sphere._r = 0.5;
    Polygon3 poly = Polygon3{Vector3{0, 0, -1}, {Vector3{-1, 0, 10}, Vector3{0, 1, 10}, Vector3{1, 0, 10}}};
    // poly._normal = Vector3{0, 0, -1};
    // poly._points.emplace_back(-1, 0, 10);
    // poly._points.emplace_back(0, 1, 10);
    // poly._points.emplace_back(1, 0, 10);
    // TaggedShape tPoly{POLYGON, poly, Color3{}};
    // parScene._hostShapes.push_back(tSphere);
    // parScene._hostShapes.emplace_back(PLANE, xzPlane, Color3{});
    parScene._hostShapes.emplace_back(PLANE, xzPlane, Color3{});
    parScene._hostShapes.emplace_back(SPHERE, sphere, Color3{});
    // parScene._hostShapes.emplace_back(POLYGON, poly, Color3{});

    Line2 verticalLine{origin2, 2 * yVec2};
    Ray2 horizontalRay{yVec2 - xVec2, xVec2};
    auto hit = intersectLine(verticalLine, horizontalRay);
    if (hit._hit)
    {
        // std::cout << verticalLine << "\n"
        //           << horizontalRay << "\n"
        //           << hit.t << "\n";
    }

    std::vector<Line2> lines;
    Line2 test{poly._points[0], poly._points[1], Y};
    lines.push_back(test);
    for (size_t i = 0, e = poly._points.size(); i < e; ++i)
    {
        // auto point = poly._points[i];
        Line2 test{poly._points[i], poly._points[i + 1], Z};
        lines.emplace_back(poly._points[i], poly._points[i + 1], Z);
        std::cout << lines[i] << "\n";
    }
    lines.emplace_back(poly._points.front(), poly._points.back(), Z);
    for (auto line : lines)
    {
        std::cout << line << "\n";
    }

    render(parScene, 100, 100);
}
