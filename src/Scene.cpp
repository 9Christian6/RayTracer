#include "Intersection.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "Vector2.hpp"
#include "RenderKernel.h"
#include <chrono>
#include <future>

namespace raytracer
{
    Scene::Scene(std::vector<Light> lights, ShapeSet shapes, Camera &cam)
        : _lights{lights}, _shapes{shapes}, _camera{cam} {};

    const ShapeSet &Scene::shapes() const
    {
        return _shapes;
    }

    const Camera &Scene::camera() const
    {
        return _camera;
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

    std::chrono::_V2::system_clock::time_point timerStart()
    {
        return std::chrono::_V2::high_resolution_clock::now();
    }

    int timerStop(std::chrono::_V2::high_resolution_clock::time_point start)
    {
        auto stop = std::chrono::_V2::high_resolution_clock::now();
        return (std::chrono::duration_cast<std::chrono::milliseconds>(stop - start)).count();
    }

    void Scene::renderSeq(int width, int height, int bounces, int samples) const
    {
        Image img{width, height};
        auto start = timerStart();
        for (size_t y = 0; y < height; y++)
        {
            for (size_t x = 0; x < width; x++)
            {
                Color pixel{0, 0, 0};
                double reflectivity{0};
                auto ray = camera().makeRay(width, height, Vector2{(int)x, (int)y});
                if (auto hit = shapes().intersect(ray))
                {
                    pixel = *hit->color(visibleLights(hit->position()));
                    ray = hit->reflectionRay();
                    reflectivity = hit->material()->specularity();
                }
                for (size_t bounce = 1; bounce < bounces; bounce++)
                {
                    if (auto hit = shapes().intersect(ray))
                    {
                        pixel += *hit->color(visibleLights(hit->position())) * reflectivity * (1 / std::pow(2, bounce));
                        ray = hit->reflectionRay();
                    }
                    else
                        break;
                }
                img.plot(x, y, pixel);
            }
        }
        img._image.close();
        auto renderTime = timerStop(start);
        std::cout << "It took " << renderTime / 1000 << "," << renderTime % 1000 << " seconds to render sequencially\n";
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

    static std::mutex s_ShapesMutex;

    void renderPixelPar(Image &img, int x, int y, const Scene *scene, int bounces)
    {
        Color pixel{0, 0, 0};
        double reflectivity{0};
        auto ray = scene->camera().makeRay(img.width(), img.height(), Vector2{x, y});
        if (auto hit = scene->shapes().intersect(ray))
        {
            pixel = *hit->color(scene->visibleLights(hit->position()));
            ray = hit->reflectionRay();
            reflectivity = hit->material()->specularity();
        }
        for (size_t bounce = 1; bounce < bounces; bounce++)
        {
            if (auto hit = scene->shapes().intersect(ray))
            {
                pixel += *hit->color(scene->visibleLights(hit->position())) * reflectivity * (1 / std::pow(2, bounce));
                ray = hit->reflectionRay();
            }
            else
                break;
        }
        img.plot(x, y, pixel);
    }

    void Scene::renderPar(int width, int height, int bounces, int samples) const
    {
        Image img{width, height};
        auto start = timerStart();
        std::vector<std::future<void>> futures;
        for (int pixel = 0; pixel < width * height; pixel++)
        {
            futures.push_back(std::async(std::launch::async, renderPixelPar, std::reference_wrapper<Image>(img), pixel % width, pixel / width, this, bounces));
        }
        img._image.close();
        auto renderTime = timerStop(start);
        std::cout << "It took " << renderTime / 1000 << "," << renderTime % 1000 << " seconds to render with std::async\n";
    }
}