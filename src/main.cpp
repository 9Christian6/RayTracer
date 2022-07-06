#include <iostream>
#include <cstring>
#include <string>
#include <math.h>
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
#include "Light.hpp"
#include "Scene.hpp"
#include "BoundingBox.hpp"
#include "CUDA.h"
#include "RenderKernel.h"
#include <cmath>
#include "CUDAShape.hpp"
#include "CUDAScene.hpp"

using namespace raytracer;
int main(int, char **)
{
    Vector origin{0, 0, 0}, xVec{1, 0, 0}, yVec{0, 1, 0}, zVec{0, 0, 1};
    Vector2 origin2{0, 0}, xVec2{1, 0}, yVec2{0, 1};
    Camera camera{yVec, zVec, yVec, 10, 1};
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
    S_Camera cam = S_Camera_new(S_vector3_new(yVec), S_vector3_new(zVec), S_vector3_new(yVec), 10, 1);
    parScene._cam = cam;
    S_plane plane;
    plane._n = S_vector3_new(yVec);
    plane._o = S_vector3_new(origin);
    T_shape tPlane;
    tPlane._shape._plane = plane;
    tPlane._tag = PLANE;
    S_sphere sphere;
    sphere._o = S_vector3_new(3 * zVec + yVec);
    sphere._r = 0.5;
    T_shape tSphere;
    tSphere._shape._sphere = sphere;
    tSphere._tag = SPHERE;

    parScene._hostShapes.push_back(tSphere);
    // parScene._hostShapes.push_back(tPlane);

    render(parScene, 200, 200);

    // TAGGED UNION STUFF

    // S_ray ray = S_ray_new(Ray{yVec, -yVec});
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
