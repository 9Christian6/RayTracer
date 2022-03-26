#pragma once
#include <math.h>
#include "PrecisionFraction.hpp"

namespace ccc
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
    inline auto equals(const pfrac::PrecisionFraction &a, const pfrac::PrecisionFraction &b)
    {
        EQUALS_IMPL(a.approxRealValue(), b.approxRealValue());
    }

#undef EQUALS_IMPL
}