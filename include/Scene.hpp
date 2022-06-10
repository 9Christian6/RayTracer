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
        ShapeSet _shapes;
        Camera &_camera;

    public:
        Scene(std::vector<Light> lights, ShapeSet shapes, Camera &cam);
        void addShape(Shape &shape);
        void addLight(Light &light);
        const Camera &camera() const;
        void setCamera(const Vector &position, const Vector &upGuide, const Vector &forward);
        void render(int width, int height, int bounces, int samples) const;
        const ShapeSet &shapes() const;
        bool isVisible(const Vector &point, const Light &light) const;
        std::vector<Light> visibleLights(const Vector &point) const;
    };

}
