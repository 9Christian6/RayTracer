#pragma once
#include "Intersection.hpp"
#include "Ray.hpp"

class Shape
{
private:
public:
    virtual bool intersect(Intersection &intersection) = 0;
    virtual bool doesIntersect(const Ray &ray) = 0;
};