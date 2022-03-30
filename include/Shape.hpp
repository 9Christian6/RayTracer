#pragma once

class Intersection;
class Ray;
class Shape
{
private:
public:
    virtual bool intersect(Intersection &intersection) = 0;
    virtual bool doesIntersect(const Ray &ray) = 0;
};