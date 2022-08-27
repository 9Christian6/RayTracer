#include <iostream>
#include <cstring>
#include <string>
#include <math.h>
#include "Exception.hpp"
#include "CUDA.h"
#include "CUDAShape.hpp"
#include "CUDAScene.hpp"
#include <cmath>

using namespace raytracer;
int main(int, char **)
{
    Vector3 origin{0, 0, 0}, xVec{1, 0, 0}, yVec{0, 1, 0}, zVec{0, 0, 1};
    // Vector2 origin2{0, 0}, xVec2{1, 0}, yVec2{0, 1};
    // Camera camera{yVec, zVec, yVec, 10, 1};
    // Sphere sphere{yVec + zVec, 0.5}, sphere2{3 * yVec + 0.5 * xVec + 2 * zVec, 0.5}, sphere3{-2 * xVec + 2 * zVec, 0.5};
    // Plane xzPlane{origin, yVec};
    // Plane yzPlane{2 * xVec, -xVec};
    // Light l1{yVec + 2 * zVec - xVec};
    // Light l2{zVec + yVec};
    // Light l3{zVec + yVec};
    // Light l4{zVec + yVec};
    // Light l5{zVec + yVec};
    // Light l6{-zVec + xVec + yVec};
    // Polygon poly{{-xVec, xVec, yVec}};
    // poly.setSpecularity(0);
    // poly.setColor(Color{1, 0, 1});
    // sphere.setColor(Color{0.6, 0, 0.6});
    // sphere2.setColor(Color{0.5, 0.5, 0});
    // sphere3.setColor(Color{0, 0.5, 0.5});
    // Sphere sphere4{0.7 * xVec + zVec, 0.5};
    // sphere4.setColor(Color{0, 0, 0});
    // sphere4.setSpecularity(1);
    // xzPlane.setColor(Color{0.2, 0.2, 0.2});
    // xzPlane.setSpecularity(0.2);
    // yzPlane.setColor(Color{0.2, 0.2, 0.2});
    // yzPlane.setSpecularity(0.2);
    // auto scene = Scene{{}, ShapeSet{{&sphere, &sphere2, &sphere3, &sphere4, &xzPlane, &yzPlane}}, camera};
    // auto scene = Scene{{}, ShapeSet{{&sphere, &xzPlane, &yzPlane}}, camera};
    // scene.addLight(l6);
    // scene.setCamera(yVec - 5 * zVec, yVec, zVec);
    // scene.renderSeq(100, 100, 2, 1);
    // scene.renderPar(100, 100, 2, 1);

    // CUDA STUFF

    CUDAScene parScene;
    parScene._lights.push_back(Vector3(3 * zVec + 4 * yVec + 4 * xVec));
    Camera cam = S_Camera_new(Vector3(yVec), Vector3(zVec), Vector3(yVec), 10, 1);
    parScene._cam = cam;
    Plane3 plane;
    plane._n = Vector3(yVec);
    plane._o = Vector3(origin);
    TaggedShape txzPlane{PLANE, plane, Color3{}};
    // txzPlane._shape._plane = plane;
    // txzPlane._tag = PLANE;
    Sphere3 sphere;
    sphere._o = Vector3(3 * zVec + yVec);
    sphere._r = 0.5;
    TaggedShape tSphere{SPHERE, sphere, Color3{}};
    // tSphere._shape._sphere = sphere;
    // tSphere._tag = SPHERE;

    parScene._hostShapes.push_back(tSphere);
    parScene._hostShapes.push_back(txzPlane);

    render(parScene, 1000, 1000);

    // TAGGED UNION STUFF

    // Ray3 ray = S_ray_new(Ray{yVec, -yVec});
    // for (auto shape : parScene._hostShapes)
    // {
    //     switch (shape._tag)
    //     {
    //     case PLANE:
    //         std::cout << "Plane\n";
    //         break;

    //     case SPHERE:
    //         std::cout << "Sphere\n";
    //         break;

    //     default:
    //         break;
    //     }
    // }
}
