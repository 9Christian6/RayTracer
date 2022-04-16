#include "Shapeset.hpp"
#include <bits/stdc++.h>
#include <vector>

namespace raytracer
{

    bool compareIntersection(const Intersection &lhs, const Intersection &rhs)
    {
        return lhs.t() < rhs.t();
    }

    void ShapeSet::addShape(Shape &shape)
    {
        _shapes.push_back(&shape);
    }

    std::optional<Intersection> ShapeSet::intersect(const Ray &ray)
    {
        std::vector<Intersection> hits;
        for (auto shape : _shapes)
        {
            if (auto hitPoint = shape->intersect(ray))
            {
                hits.push_back(hitPoint.value());
            }
        }
        if (hits.size() == 0)
            return {};
        std::size_t temp = 0;
        for (std::size_t i = 0; i < hits.size(); i++)
        {
            if (hits[temp].t() > hits[i].t())
                temp = i;
        }
        return hits[temp];
        // if (hits.size() > 0)
        //     return hits.front();
        // if (hits.size() > 0)
        // {
        //     std::sort(hits.begin(), hits.end(), compareIntersection);
        //     return hits.front();
        // }
    }
}