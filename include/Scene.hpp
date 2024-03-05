#pragma once
#include "Camera.hpp"
#include "Intersection.hpp"
#include "Light.hpp"
#include "Shapeset.hpp"
#include <vector>

namespace objl
{
  class Loader;
}

namespace raytracer
{
  class Scene
  {
  private:
    std::vector<Light> _lights;
    ShapeSet _shapes;
    Camera &_camera;
    Color renderPixel(Ray &ray) const;

  public:
    Scene(std::vector<Light> lights, ShapeSet shapes, Camera &cam);
    void addShape(Shape *shape);
    void addShapes(std::unique_ptr<objl::Loader> loader);
    void addLight(Light &light);
    void setCamera(const Vector &position, const Vector &upGuide,
                   const Vector &forward);
    void render(int width, int height) const;
    bool isVisible(const Vector &point, const Light &light) const;
    std::vector<Light> visibleLights(const Vector &point) const;
    std::vector<Light> visibleLights(const Intersection &hit) const;
  };

} // namespace raytracer
