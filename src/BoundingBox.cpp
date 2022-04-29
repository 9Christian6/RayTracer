#include "BoundingBox.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include "fEquals.hpp"
#include <limits>
#include <bits/stdc++.h>

namespace raytracer
{
    BoundingBox::BoundingBox(Vector &&minExt, Vector &&maxExt) : _minExt{std::move(minExt)}, _maxExt{std::move(maxExt)}
    {
    }

    BoundingBox::BoundingBox(Vector &minExt, Vector &&maxExt) : _minExt{minExt}, _maxExt{std::move(maxExt)}
    {
    }

    BoundingBox::BoundingBox(Vector &&minExt, Vector &maxExt) : _minExt{std::move(minExt)}, _maxExt{maxExt}
    {
    }

    BoundingBox::BoundingBox(Vector &minExt, Vector &maxExt) : _minExt{minExt}, _maxExt{maxExt}
    {
    }

    bool BoundingBox::intersect(const Ray &ray)
    {
        double tNear = std::numeric_limits<double>::lowest();
        double tFar = std::numeric_limits<double>::max();
        double xMin{_minExt.x()}, xMax{_maxExt.x()};
        double yMin{_minExt.y()}, yMax{_maxExt.y()};
        double zMin{_minExt.z()}, zMax{_maxExt.z()};
        // test for x axis aligned planes
        if (equals(ray.direction().x(), 0.))
        {
            if (ray.origin().x() < xMin || ray.origin().x() > xMax)
                return false;
        }
        else
        {
            double t1, t2;
            t1 = (xMin - ray.origin().x()) / ray.direction().x();
            t2 = (xMax - ray.origin().x()) / ray.direction().x();
            if (t1 > t2)
                std::swap(t1, t2);
            if (t1 > tNear)
                tNear = t1;
            if (t2 < tFar)
                tFar = t2;
            if (tNear > tFar)
                return false;
            if (tFar < 0)
                return false;
        }
        // test for y axis aligned planes
        if (equals(ray.origin().y(), 0.))
        {
            if (ray.origin().y() < yMin || ray.origin().y() > yMax)
                return false;
        }
        else
        {
            double t1, t2;
            t1 = (yMin - ray.origin().y()) / ray.direction().y();
            t2 = (yMax - ray.origin().y()) / ray.direction().y();
            if (t1 > t2)
                std::swap(t1, t2);
            if (t1 > tNear)
                tNear = t1;
            if (t2 < tFar)
                tFar = t2;
            if (tNear > tFar)
                return false;
            if (tFar < 0)
                return false;
        }
        // test for z axis aligned planes
        if (equals(ray.origin().z(), 0.))
        {
            if (ray.origin().z() < zMin || ray.origin().z() > zMax)
                return false;
        }
        else
        {
            double t1, t2;
            t1 = (zMin - ray.origin().z()) / ray.direction().z();
            t2 = (zMax - ray.origin().z()) / ray.direction().z();
            if (t1 > t2)
                std::swap(t1, t2);
            if (t1 > tNear)
                tNear = t1;
            if (t2 < tFar)
                tFar = t2;
            if (tNear > tFar)
                return false;
            if (tFar < 0)
                return false;
        }
        return true;
    }
}