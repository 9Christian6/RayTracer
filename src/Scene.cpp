#include "Intersection.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "Vector2.hpp"

namespace raytracer
{
    Scene::Scene(std::vector<Light> lights, ShapeSet shapes, Camera &cam)
        : _lights{lights}, _shapes{shapes}, _camera{cam} {};

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

    void Scene::render(int width, int height) const
    {
        Image img{width, height};
        for (int x = 0; x <= width; x++)
        {
            for (int y = 0; y <= height; y++)
            {
                Color pixel{0, 0, 0};
                auto ray = _camera.makeRay(width, height, Vector2{x, y});
                if (auto hit = _shapes.intersect(ray))
                {
                    pixel = *hit->color(visibleLights(hit->position()));
                    ray = hit->reflectionRay();
                    if (auto reflectionHit = _shapes.intersect(ray))
                    {
                        auto lights = visibleLights(reflectionHit->position());
                        if (reflectionHit->material())
                        {
                            pixel += reflectionHit->color(lights).value() * hit->material()->specularity();
                        }
                    }
                }
                img.plot(x, y, pixel);
            }
        }
        img._image.close();
    }

    bool Scene::isVisible(const Vector &point, const Light &light) const
    {
        Ray lightRay{light.position(), point - light.position()};
        double tLength{(light.position() - point).length()};
        if (auto lightHit = _shapes.intersect(lightRay))
        {
            return (tLength < lightHit->t() + Ray::RAY_T_MIN);
        }
        return true;
    }

    std::vector<Light> Scene::visibleLights(const Vector &point) const
    {
        std::vector<Light> lights{};
        for (auto light : _lights)
        {
            if (isVisible(point, light))
                lights.push_back(light);
        }
        return lights;
    }
}