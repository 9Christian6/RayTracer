#pragma once
#include <math.h>

namespace raytracer
{
#define EQUALS_IMPL(__a, __b)          \
    static constexpr auto eps = 10e-5; \
    return std::abs(__a - __b) <= eps

    inline auto equals(float a, float b)
    {
        EQUALS_IMPL(a, b);
    }
    inline auto equals(double a, double b)
    {
        EQUALS_IMPL(a, b);
    }
#undef EQUALS_IMPL
}