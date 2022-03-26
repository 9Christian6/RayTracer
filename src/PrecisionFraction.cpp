#include "PrecisionFraction.hpp"
#include <iostream>

namespace pfrac
{
    // Constructors
    PrecisionFraction::PrecisionFraction()
    {
        mpq_init(_frac);
        mpq_set_si(_frac, 0, 1);
        _fracDouble = mpq_get_d(_frac);
        _fracStr = "0";
    }

    PrecisionFraction::PrecisionFraction(int num)
    {
        mpq_init(_frac);
        mpq_set_si(_frac, num, 1);
        mpq_canonicalize(_frac);
        _fracDouble = mpq_get_d(_frac);
        _fracStr = std::to_string(num);
    }

    PrecisionFraction::PrecisionFraction(mpq_t frac)
    {
        mpq_init(_frac);
        mpq_set(_frac, frac);
        mpq_canonicalize(_frac);
        mpq_class str(_frac);
        _fracDouble = str.get_d();
        _fracStr = str.get_str();
    }

    PrecisionFraction::PrecisionFraction(const mpq_class &frac)
    {
        mpq_init(_frac);
        mpq_set(_frac, frac.get_mpq_t());
        mpq_canonicalize(_frac);
        _fracDouble = frac.get_d();
        _fracStr = frac.get_str();
    }

    PrecisionFraction::PrecisionFraction(signed long num, long denom)
    {
        mpq_init(_frac);
        mpq_set_si(_frac, num, denom);
        mpq_canonicalize(_frac);
        _fracDouble = mpq_get_d(_frac);
        _fracStr = std::to_string(num) + "/" + std::to_string(denom);
    }

    PrecisionFraction::PrecisionFraction(signed long num)
    {
        mpq_init(_frac);
        mpq_set_si(_frac, num, 1);
        mpq_canonicalize(_frac);
        _fracDouble = mpq_get_d(_frac);
        _fracStr = std::to_string(num);
    }

    PrecisionFraction::PrecisionFraction(double d)
    {
        mpq_init(_frac);
        mpq_set_d(_frac, d);
        mpq_canonicalize(_frac);
        _fracDouble = mpq_get_d(_frac);
        mpq_class str(_frac);
        _fracStr = str.get_str();
    }

    PrecisionFraction::PrecisionFraction(const PrecisionFraction &frac)
    {
        mpq_init(_frac);
        mpq_set(_frac, frac._frac);
        mpq_canonicalize(_frac);
        _fracDouble = frac._fracDouble;
        mpq_class str(_frac);
        _fracStr = str.get_str();
    }

    MP_INT PrecisionFraction::numerator() const
    {
        return _frac->_mp_num;
    }

    MP_INT PrecisionFraction::denominator() const
    {
        return _frac->_mp_den;
    }

    int PrecisionFraction::sign() const
    {
        return mpq_sgn(_frac);
    }

    double PrecisionFraction::approxRealValue() const
    {
        return _fracDouble;
    }

    void PrecisionFraction::set(signed long num)
    {
        mpq_set_si(_frac, num, 1);
        mpq_canonicalize(_frac);
        _fracDouble = mpq_get_d(_frac);
        _fracStr = std::to_string(num);
    }

    void PrecisionFraction::set(signed long num, long denom)
    {
        mpq_set_si(_frac, num, denom);
        mpq_canonicalize(_frac);
        _fracDouble = num / denom;
        _fracStr = std::to_string(num) + "/" + std::to_string(denom);
    }

    void PrecisionFraction::setNum(signed long num)
    {
        mpz_t newNum;
        mpz_init_set_si(newNum, num);
        mpq_set_num(_frac, newNum);
        mpq_canonicalize(_frac);
        _fracDouble = mpq_get_d(_frac);
        _fracStr = std::to_string(num);
    }

    void PrecisionFraction::setDenom(signed long denom)
    {
        mpz_t newDenom;
        mpz_init_set_si(newDenom, denom);
        mpq_set_den(_frac, newDenom);
        mpq_canonicalize(_frac);
        _fracDouble = mpq_get_d(_frac);
        mpq_class str(_frac);
        _fracStr = str.get_str();
    }

    void PrecisionFraction::negate()
    {
        mpq_neg(_frac, _frac);
        _fracDouble *= -1;
        mpq_class str(_frac);
        _fracStr = str.get_str();
    }

    void PrecisionFraction::properize()
    {
        mpq_canonicalize(_frac);
        mpq_class str(_frac);
        _fracStr = str.get_str();
    }

    void PrecisionFraction::invert()
    {
        mpq_inv(_frac, _frac);
        _fracDouble = 1 / _fracDouble;
        mpq_class str(_frac);
        _fracStr = str.get_str();
    }

    bool operator==(const PrecisionFraction &lhs, PrecisionFraction &rhs)
    {
        return mpq_equal(lhs._frac, rhs._frac) != 0;
    }

    bool operator==(const PrecisionFraction &lhs, const PrecisionFraction &rhs)
    {
        return mpq_equal(lhs._frac, rhs._frac) != 0;
    }

    bool operator!=(const PrecisionFraction &lhs, PrecisionFraction &rhs)
    {
        return !(lhs == rhs);
    }

    bool operator!=(const PrecisionFraction &lhs, const PrecisionFraction &rhs)
    {
        return !(lhs == rhs);
    }

    bool operator>(const PrecisionFraction &lhs, PrecisionFraction &rhs)
    {
        return mpq_cmp(lhs._frac, rhs._frac) > 0;
    }

    bool operator<(const PrecisionFraction &lhs, PrecisionFraction &rhs)
    {
        return mpq_cmp(lhs._frac, rhs._frac) < 0;
    }

    bool operator>(const PrecisionFraction &lhs, const PrecisionFraction &rhs)
    {
        return mpq_cmp(lhs._frac, rhs._frac) > 0;
    }

    bool operator<(const PrecisionFraction &lhs, const PrecisionFraction &rhs)
    {
        return mpq_cmp(lhs._frac, rhs._frac) < 0;
    }

    bool operator>=(const PrecisionFraction &lhs, PrecisionFraction &rhs)
    {
        return (lhs._frac == rhs._frac || lhs._frac > rhs._frac);
    }

    bool operator<=(const PrecisionFraction &lhs, PrecisionFraction &rhs)
    {
        return (lhs._frac == rhs._frac || lhs._frac < rhs._frac);
    }

    bool operator>=(const PrecisionFraction &lhs, const PrecisionFraction &rhs)
    {
        return (lhs._frac == rhs._frac || lhs._frac > rhs._frac);
    }

    bool operator<=(const PrecisionFraction &lhs, const PrecisionFraction &rhs)
    {
        return (lhs._frac == rhs._frac || lhs._frac < rhs._frac);
    }

    PrecisionFraction operator-(const PrecisionFraction &frac)
    {
        PrecisionFraction negatedFrac(frac);
        negatedFrac *= -1;
        return negatedFrac;
    }

    PrecisionFraction operator+(const PrecisionFraction &lhs, const PrecisionFraction &rhs)
    {
        PrecisionFraction sum = PrecisionFraction();
        mpq_add(sum._frac, lhs._frac, rhs._frac);
        mpq_canonicalize(sum._frac);
        sum._fracDouble = lhs._fracDouble + rhs._fracDouble;
        sum.properize();
        return sum;
    }

    PrecisionFraction operator-(const PrecisionFraction &lhs, const PrecisionFraction &rhs)
    {
        PrecisionFraction dif = PrecisionFraction();
        mpq_sub(dif._frac, lhs._frac, rhs._frac);
        mpq_canonicalize(dif._frac);
        dif._fracDouble = lhs._fracDouble - rhs._fracDouble;
        dif.properize();
        return dif;
    }

    PrecisionFraction operator*(const PrecisionFraction &lhs, const PrecisionFraction &rhs)
    {
        PrecisionFraction prod;
        mpq_mul(prod._frac, lhs._frac, rhs._frac);
        mpq_canonicalize(prod._frac);
        prod._fracDouble = lhs._fracDouble * rhs._fracDouble;
        prod.properize();
        return prod;
    }

    PrecisionFraction operator/(const PrecisionFraction &lhs, const PrecisionFraction &rhs)
    {
        PrecisionFraction div = PrecisionFraction();
        mpq_div(div._frac, lhs._frac, rhs._frac);
        mpq_canonicalize(div._frac);
        div._fracDouble = lhs._fracDouble / rhs._fracDouble;
        div.properize();
        return div;
    }

    PrecisionFraction operator+=(PrecisionFraction &lhs, const PrecisionFraction &rhs)
    {
        lhs = lhs + rhs;
        return lhs;
    }

    PrecisionFraction operator-=(PrecisionFraction &lhs, const PrecisionFraction &rhs)
    {
        lhs = lhs - rhs;
        return lhs;
    }

    PrecisionFraction operator*=(PrecisionFraction &lhs, const PrecisionFraction &rhs)
    {
        lhs = lhs * rhs;
        return lhs;
    }

    PrecisionFraction operator/=(PrecisionFraction &lhs, const PrecisionFraction &rhs)
    {
        lhs = lhs / rhs;
        return lhs;
    }

    ostream &
    operator<<(ostream &output, const PrecisionFraction &frac)
    {
        output << frac._frac;
        // if (frac._fracDouble == 0)
        //     output << 0;
        // else
        //     output << frac._fracDouble;
        return output;
    }
}