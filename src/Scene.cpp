#include "Scene.hpp"
#include "Camera.hpp"

namespace raytracer
{
    Scene::Scene(std::vector<Light> lights, ShapeSet &shapes, Camera &cam)
        : _lights{lights}, _shapes{shapes}, _camera{cam} {};
}