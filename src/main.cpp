#include <iostream>
#include "Ray.hpp"
#include "Vector.hpp"
#include "Exception.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "Image.hpp"
#include <cmath>
// std::cout.setf(std::ios::boolalpha);

int main(int, char **)
{
    Vector origin{0, 0, 0}, xVec{1, 0, 0}, yVec{0, 1, 0}, zVec{0, 0, 1};
    Camera camera{yVec, zVec + yVec, 2 * yVec, 90, 1};
    Image image{100, 100};
    Sphere sphere{10 * zVec, 5};
    auto xzPlane = Plane{origin, yVec};
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            auto ray = camera.makeRay(image, Vector2{x, y});
            auto hit = ray.hit(sphere);
            if (hit)
            {
                image.setPixel(x, y, true);
                continue;
            }
            std::cout << ray << "\n";
        }
    }
    image.print();
}
