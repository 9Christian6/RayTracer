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
                    auto hitPositionExtruded = hitPosition + 0.25 * intersection->normal();
                    double color{0};
                    for (auto light : _lights)
                    {
                        auto lightTest = Ray{hitPosition, light.position()};
                        if (!_shapes.intersect(lightTest))
                        {
                            Vector eyeDirection = ray.direction();
                            Vector lightDirection = (light.position() - hitPosition).normalize();
                            Vector normal = intersection->normal();
                            double angle = normal.angle(lightDirection);
                            color += 1 - angle / 180.;
                        }
                    }
                    img._image.plot(x, y, color, color, color);
                }
            }
        }
        img._image.close();
    }

    void Scene::addShape(Shape &shape)
    {
        _shapes.addShape(shape);
    }

    void Scene::addLight(Light &light)
    {
        _lights.push_back(light);
    }

    void Scene::setCamera(const Vector &position, const Vector &upGuide, const Vector &forward)
    {
        _camera.setPosition(position, upGuide, forward);
    }
}