#include "Scene.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "Vector2.hpp"

namespace raytracer
{
    Scene::Scene(std::vector<Light> lights, ShapeSet &shapes, Camera &cam)
        : _lights{lights}, _shapes{shapes}, _camera{cam} {};

    void Scene::render(int width, int height) const
    {
        auto img = Image{width, height};
        for (int x = 0; x <= width; x++)
        {
            for (int y = 0; y <= height; y++)
            {
                auto ray = _camera.makeRay(width, height, Vector2{x, y});
                if (auto intersection = _shapes.intersect(ray))
                {
                    auto hitPosition = intersection->position();
                    auto lights = _shapes.visibleLights(hitPosition + (1 + Ray::RAY_T_MIN) * intersection->normal());
                    double color = 1;
                    if (!lights.empty())
                    {
                        for (auto light : lights)
                        {
                            Vector eyeDirection = ray.direction();
                        }
                    }
                    img._image.plot(x, y, 1., 1., 1.);
                }
            }
        }
        img._image.close();
    }

    void Scene::addShape(Shape &shape)
    {
        _shapes.addShape(shape);
    }
}