#pragma once
#include <ostream>
using std::ostream;
#include <gmpxx.h>
#include <Eigen/Core>

namespace pfrac
{
    class PrecisionFraction
    {
    public:
        mpq_t _frac;
        double _fracDouble;
        static bool _precise;

        PrecisionFraction();
        PrecisionFraction(int num);
        PrecisionFraction(mpq_t frac);
        PrecisionFraction(signed long num, long denom);
        PrecisionFraction(signed long num);
        PrecisionFraction(double d);
        PrecisionFraction(const PrecisionFraction &frac);
        PrecisionFraction(const mpq_class &frac);
        MP_INT numerator() const;
        MP_INT denominator() const;
        int sign() const;
        double approxRealValue() const;
        void set(signed long num);
        void set(signed long num, long denom);
        void setNum(signed long num);
        void setDenom(long denom);
        void negate();
        void properize();
        void invert();

        friend bool operator==(const PrecisionFraction &lhs, PrecisionFraction &rhs);
        friend bool operator==(const PrecisionFraction &lhs, const PrecisionFraction &rhs);
        friend bool operator!=(const PrecisionFraction &lhs, PrecisionFraction &rhs);
        friend bool operator!=(const PrecisionFraction &lhs, const PrecisionFraction &rhs);
        friend bool operator>(const PrecisionFraction &lhs, PrecisionFraction &rhs);
        friend bool operator<(const PrecisionFraction &lhs, PrecisionFraction &rhs);
        friend bool operator>(const PrecisionFraction &lhs, const PrecisionFraction &rhs);
        friend bool operator<(const PrecisionFraction &lhs, const PrecisionFraction &rhs);
        friend bool operator>=(const PrecisionFraction &lhs, PrecisionFraction &rhs);
        friend bool operator<=(const PrecisionFraction &lhs, PrecisionFraction &rhs);
        friend bool operator>=(const PrecisionFraction &lhs, const PrecisionFraction &rhs);
        friend bool operator<=(const PrecisionFraction &lhs, const PrecisionFraction &rhs);
        friend PrecisionFraction operator+(const PrecisionFraction &lhs, const PrecisionFraction &rhs);
        friend PrecisionFraction operator-(const PrecisionFraction &lhs, const PrecisionFraction &rhs);
        friend PrecisionFraction operator*(const PrecisionFraction &lhs, const PrecisionFraction &rhs);
        friend PrecisionFraction operator/(const PrecisionFraction &lhs, const PrecisionFraction &rhs);
        friend PrecisionFraction operator-(const PrecisionFraction &frac);
        friend PrecisionFraction operator+=(PrecisionFraction &lhs, const PrecisionFraction &rhs);
        friend PrecisionFraction operator-=(PrecisionFraction &lhs, const PrecisionFraction &rhs);
        friend PrecisionFraction operator*=(PrecisionFraction &lhs, const PrecisionFraction &rhs);
        friend PrecisionFraction operator/=(PrecisionFraction &lhs, const PrecisionFraction &rhs);

        friend ostream &operator<<(ostream &out, const PrecisionFraction &frac);

    private:
        void recude();
        void print(std::ostream &stream) const;
        int compare(PrecisionFraction pf) const;
        std::string _fracStr;
    };

    inline PrecisionFraction sqrt(const PrecisionFraction &frac)
    {
        return PrecisionFraction{std::sqrt(frac.approxRealValue())};
    }

    inline PrecisionFraction abs(const PrecisionFraction &f)
    {
        mpq_t temp;
        mpq_init(temp);
        mpq_abs(temp, f._frac);
        return PrecisionFraction(temp);
    }

    inline bool isfinite(const PrecisionFraction &f)
    {
        return true;
    }
}

template <>
struct Eigen::NumTraits<pfrac::PrecisionFraction>
{
    using frac = pfrac::PrecisionFraction;
    typedef frac Real;
    typedef frac NonInteger;
    typedef frac Literal;
    typedef frac Nested;
    enum
    {
        IsComplex = 0,
        IsInteger = 0,
        IsSigned = 1,
        RequireInitialization = 1,
        ReadCost = Eigen::HugeCost,
        AddCost = Eigen::HugeCost,
        MulCost = Eigen::HugeCost
    };
    inline double log10(frac f) { return std::log10(f.approxRealValue()); }
    inline static Real epsilon() { return frac(0); }
    inline static frac dummy_precision() { return frac(1, 1000); }
    inline static frac highest() { return frac(std::numeric_limits<signed long long int>::max(), 1); }
    inline static frac lowest() { return frac(1, std::numeric_limits<signed long long int>::max()); }
    inline static int digits() { return 13; }
    inline static double digits10() { return std::numeric_limits<unsigned long long>::digits * std::log10(2); }
    inline static int min_exponent() { return 0; }
    inline static int max_exponent() { return 0; }
};

namespace std
{
    template <>
    struct hash<pfrac::PrecisionFraction>
    {
        auto operator()(const pfrac::PrecisionFraction &frac) const noexcept -> std::size_t
        {
            return std::hash<double>{}(frac.approxRealValue());
        }
    };
}