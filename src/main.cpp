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
#include "shape.hpp"
#include <cmath>

using namespace raytracer;
int main(int, char **)
{
    S_vector3 o;
    o._x = 0;
    o._y = 0;
    o._z = 0;

    S_vector3 s_xvec;
    s_xvec._x = 1;
    s_xvec._y = 0;
    s_xvec._z = 0;

    S_sphere s;
    s._origin = o;
    s._r = 1;

    S_plane p;
    p._origin = o;
    p._normal = s_xvec;

    S_ray r;
    r._o = o;
    r._d = s_xvec;

    T_shape shape;
    shape.tag = SPHERE;
    shape.shape._sphere = s;

    auto intersection = intersect(shape, r);

    std::cout << intersection.t << "\n";

    Vector origin{0, 0, 0}, xVec{1, 0, 0}, yVec{0, 1, 0}, zVec{0, 0, 1};
    Vector2 origin2{0, 0}, xVec2{1, 0}, yVec2{0, 1};
    //
    //
    //
    Camera camera{yVec, zVec, yVec, 10, 1};
    Sphere sphere{yVec - 0.5 * xVec + 2 * zVec, 0.5}, sphere2{3 * yVec + 0.5 * xVec + 2 * zVec, 0.5}, sphere3{-2 * xVec + 2 * zVec, 0.5};
    Plane xzPlane{origin, yVec};
    Plane yzPlane{2 * xVec, -xVec};
    Light l1{yVec + 2 * zVec - xVec};
    Light l2{zVec + yVec};
    Light l3{zVec + yVec};
    Light l4{zVec + yVec};
    Light l5{zVec + yVec};
    Polygon poly{{-xVec, xVec, yVec}};
    poly.setSpecularity(0);
    poly.setColor(Color{1, 0, 1});
    sphere.setColor(Color{0.6, 0, 0.6});
    sphere2.setColor(Color{0.5, 0.5, 0});
    sphere3.setColor(Color{0, 0.5, 0.5});
    Sphere sphere4{0.7 * xVec + zVec, 0.5};
    sphere4.setColor(Color{0, 0, 0});
    sphere4.setSpecularity(1);
    xzPlane.setColor(Color{0.2, 0.2, 0.2});
    yzPlane.setColor(Color{0.2, 0.2, 0.2});
    xzPlane.setSpecularity(0);
    yzPlane.setSpecularity(0.2);
    //
    //
    //
    //
    auto scene = Scene{{}, ShapeSet{{&sphere, &sphere2, &sphere3, &sphere4, &xzPlane, &yzPlane}}, camera};
    scene.addLight(l2);
    scene.addLight(l3);
    scene.setCamera(yVec - 5 * zVec, yVec, zVec);
    scene.renderSeq(100, 100, 1, 1);
    scene.renderPar(100, 100, 1, 1);
}
