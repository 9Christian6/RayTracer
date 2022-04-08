#pragma once
#include <optional>
#include "fEquals.hpp"

namespace raytracer
{
    std::optional<double> scalarQuotient(double a, double b)
    {
        std::optional<double> s;
        if (!equals(a, 0))
            s.emplace(b / a);
        return s;
    }
}