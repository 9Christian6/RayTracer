#pragma once
#include "Vector.hpp"

namespace raytracer
{
    enum class Dimension;
    class Ray;
    class BoundingBox
    {
    private:
        Vector m_min, m_max;

    public:
        BoundingBox() = default;
        BoundingBox(Vector &&minExt, Vector &&maxExt);
        BoundingBox(Vector &minExt, Vector &&maxExt);
        BoundingBox(Vector &&minExt, Vector &maxExt);
        BoundingBox(Vector &minExt, Vector &maxExt);
        Vector minExt() const;
        Vector maxExt() const;
        bool intersect(const Ray &ray);
        void extend(const Vector& point);
	void extend(const BoundingBox& box);
        Dimension longestDim();
	friend std::ostream &operator<<(std::ostream &out, const BoundingBox box);
    };
}
