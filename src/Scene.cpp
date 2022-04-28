#include "Intersection.hpp"
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
                    auto normal = intersection->normal();
                    auto hitPosition = intersection->position();
                    double color{0};
                    for (auto light : _lights)
                    {
                        if (isVisible(*intersection, light))
                        {
                            auto lightDirection = (light.position() - hitPosition).normalize();
                            color += 0.5 * (normal * lightDirection);
                        }
                    }
                    img._image.plot(x, y, color, color, color);
                }
            }
        }
        img._image.close();
    }

    bool Scene::isVisible(const Intersection &point, const Light &light) const
    {
        Vector position = point.position() + Ray::RAY_T_MIN * point.normal();
        Ray lightRay{light.position(), position - light.position()};
        double tLength{(light.position() - point.position()).length()};
        if (auto lightHit = _shapes.intersect(lightRay))
        {
            return (tLength < lightHit->t());
        }
        return true;
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