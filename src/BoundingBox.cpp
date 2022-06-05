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

    Vector BoundingBox::minExt() const
    {
        return _minExt;
    }

    Vector BoundingBox::maxExt() const
    {
        return _maxExt;
    }

    enum Dimension
    {
        x,
        y,
        z
    };

    bool hitTest(Dimension dim, const Ray &ray, double min, double max)
    {
        double tNear = std::numeric_limits<double>::lowest();
        double tFar = std::numeric_limits<double>::max();
        double rayO, rayD, t1, t2;
        switch (dim)
        {
        case x:
            rayO = ray.origin().x();
            rayD = ray.direction().x();
            break;

        case y:
            rayO = ray.origin().y();
            rayD = ray.direction().y();
            break;

        case z:
            rayO = ray.origin().z();
            rayD = ray.direction().z();
            break;
        }
        t1 = (min - rayO) / rayD;
        t2 = (max - rayO) / rayD;
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
        return true;
    }

    bool BoundingBox::intersect(const Ray &ray)
    {
        double tNear = std::numeric_limits<double>::lowest();
        double tFar = std::numeric_limits<double>::max();
        double xMin{_minExt.x()}, xMax{_maxExt.x()};
        double yMin{_minExt.y()}, yMax{_maxExt.y()};
        double zMin{_minExt.z()}, zMax{_maxExt.z()};
        if (equals(ray.direction().x(), 0.))
        {
            if (ray.origin().x() < xMin || ray.origin().x() > xMax)
                return false;
        }
        else
        {
            if (!hitTest(Dimension::x, ray, xMin, xMax))
                return false;
        }
        if (equals(ray.origin().y(), 0.))
        {
            if (ray.origin().y() < yMin || ray.origin().y() > yMax)
                return false;
        }
        else
        {
            if (!hitTest(Dimension::y, ray, yMin, yMax))
                return false;
        }
        if (equals(ray.origin().z(), 0.))
        {
            if (ray.origin().z() < zMin || ray.origin().z() > zMax)
                return false;
        }
        else
        {
            if (!hitTest(Dimension::z, ray, zMin, zMax))
                return false;
        }
        return true;
    }

}