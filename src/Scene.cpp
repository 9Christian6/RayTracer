#include "Intersection.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "Vector2.hpp"
#include <chrono>

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
        using std::chrono::duration;
        using std::chrono::duration_cast;
        using std::chrono::high_resolution_clock;
        using std::chrono::milliseconds;
        auto t1 = high_resolution_clock::now();

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

        auto t2 = high_resolution_clock::now();
        /* Getting number of milliseconds as an integer. */
        auto ms_int = duration_cast<milliseconds>(t2 - t1);
        std::cout << "It took " << ms_int.count() << " milliseconds to render\n";
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