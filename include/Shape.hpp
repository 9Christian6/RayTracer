#pragma once
#include <optional>

class Intersection;
class Ray;
class Shape
{
private:
public:
    virtual std::optional<Intersection> intersect(const Ray &ray) = 0;
};