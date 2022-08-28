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
    Plane3 plane;
    plane._n = Vector3(yVec);
    plane._o = Vector3(origin);
    TaggedShape txzPlane{PLANE, plane, Color3{}};
    Sphere3 sphere;
    sphere._o = Vector3(3 * zVec + yVec);
    sphere._r = 0.5;
    TaggedShape tSphere{SPHERE, sphere, Color3{}};
    parScene._hostShapes.push_back(tSphere);
    parScene._hostShapes.push_back(txzPlane);

    render(parScene, 1000, 1000);
}
