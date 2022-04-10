#pragma once
#include <optional>
#include "fEquals.hpp"

namespace raytracer
{
    inline std::optional<double> scalarQuotient(double a, double b)
    {
        if (!equals(a, 0))
            return b / a;
        return {};
    }
}