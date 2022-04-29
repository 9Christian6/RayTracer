#pragma once
#include <optional>
#include "Intersection.hpp"
#include "Ray.hpp"

class IIntersectable
{
private:
public:
    virtual ~IIntersectable() = default;
    virtual std::optional<Intersection> intersect(const Ray &ray) = 0;
};