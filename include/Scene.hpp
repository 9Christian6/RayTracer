#pragma once
#include "Intersection.hpp"
#include "Shapeset.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include "Image.hpp"
#include <vector>

namespace raytracer
{
    class Scene
    {
    private:
        std::vector<Light> _lights;
        ShapeSet &_shapes;
        Camera &_camera;

    public:
        Scene(std::vector<Light> lights, ShapeSet &shapes, Camera &cam);
        void addShape(Shape &shape);
        void addLight(Light &light);
        void setCamera(const Vector &position, const Vector &upGuide, const Vector &forward);
        void render(int width, int height) const;
        bool isVisible(const Intersection &point, const Light &light) const;
    };

}
