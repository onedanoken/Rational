#include <iostream>
#include <stdexcept>

class RationalDivisionByZero : public std::runtime_error {
public:
    RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
    }
};

class Rational {
public:
    Rational();
    Rational(const int32_t value); // NOLINT
    Rational(const int32_t Numerator, const int Denominator);

    friend std::ostream& operator<<(std::ostream& out, const Rational& num);
    friend std::istream& operator>>(std::istream& in, Rational& num);

    void SetNumerator(int32_t Numerator_);
    int GetNumerator() const;
    void SetDenominator(int32_t Denominator_);
    int GetDenominator() const;

    Rational operator=(const int32_t value);
    Rational operator=(const Rational& other);
    Rational operator+(const Rational& other);
    Rational operator+=(const Rational& other);
    Rational operator-(const Rational& other);
    Rational operator-=(const Rational& other);
    Rational operator*(const Rational& other);
    Rational operator*=(const Rational& other);
    Rational operator/(const Rational& other);
    Rational operator/=(const Rational& other);
    Rational operator-() const;

    Rational operator++();
    Rational operator++(int);
    Rational operator--();
    Rational operator--(int);

    bool operator<(const Rational& other) const;
    bool operator>(const Rational& other) const;
    bool operator>=(const Rational& other) const;
    bool operator<=(const Rational& other) const;
    bool operator==(const Rational& other) const;
    bool operator!=(const Rational& other) const;

private:
    int Numerator;
    int Denominator;

    void reduce();
    int gcd(int32_t a, int32_t b) const;
};