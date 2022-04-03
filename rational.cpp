#pragma once
#include "rational.h"

std::ostream& operator<<(std::ostream& out, const Rational& num) {
    out << num.Numerator;
    if (num.Numerator != 0 && num.Denominator != 1) {
        out << "/" << num.Denominator;
    }
    return out;
}

std::istream& operator>>(std::istream& in, Rational& num) {
    char separator;
    in >> num.Numerator >> separator >> num.Denominator;
    if (num.Denominator < 0) {
        num.Numerator = -num.Numerator;
        num.Denominator = -num.Denominator;
    }
    num.reduce();
    return in;
}

Rational::Rational(): Numerator(0), Denominator(1) {}

Rational::Rational(const int32_t value) : Numerator(value), Denominator(1) {}

Rational::Rational(const int32_t Numerator, const int32_t Denominator_) : Numerator(Numerator) {
    if (Denominator_ == 0)
       /* throw RationalDivisionByZero();*/

    Denominator = Denominator_;
    if (this->Denominator < 0) {
        this->Numerator = -this->Numerator;
        this->Denominator = -this->Denominator;
    }
    reduce();
}

void Rational::SetNumerator(int32_t Numerator_) {
    Numerator = Numerator_;
    reduce();
}

int Rational::GetNumerator() const { 
    return Numerator; 
}

void Rational::SetDenominator(int32_t Denominator_) {
    if (Denominator_ == 0) {
        throw RationalDivisionByZero();
    }
    else {
        Denominator = Denominator_;
        reduce();
    }
}

int Rational::GetDenominator() const { 
    return Denominator; 
}

Rational Rational::operator=(const int32_t value) {
    Numerator = value;
    Denominator = 1;
    return *this;
}

Rational Rational::operator=(const Rational& other) {
    Numerator = other.Numerator;
    Denominator = other.Denominator;
    return *this;
}

Rational Rational::operator+(const Rational& other) {
    return Rational{ Numerator * other.Denominator + Denominator * other.Numerator, Denominator * other.Denominator };
}

Rational Rational::operator+=(const Rational& other) {
    return *this + other;
}

Rational Rational::operator-(const Rational& other) {
    return -other + *this;
}

Rational Rational::operator-=(const Rational& other) {
    return *this - other;
}

Rational Rational::operator*(const Rational& other) {
    return Rational(Numerator * other.Numerator, Denominator * other.Denominator);
}

Rational Rational::operator*=(const Rational& other) {
    return *this * other;
}

Rational Rational::operator/(const Rational& other) {
    *this = Rational(Numerator * other.Denominator, Denominator * other.Numerator);
    return *this;

}

Rational Rational::operator/=(const Rational& other) {
    return *this / other;
}

Rational Rational::operator-() const {
    return Rational(-Numerator, Denominator);
}

Rational Rational::operator++() {
    *this = *this + 1;
    return *this;
}

Rational Rational::operator++(int) {
    Rational before = *this;
    *this = *this + 1;
    return before;
}

Rational Rational::operator--() {
    *this = *this - 1;
    return *this;
}

Rational Rational::operator--(int) {
    Rational before = *this;
    *this = *this - 1;
    return before;
}

bool Rational::operator<(const Rational& other) const {
    return Numerator * other.Denominator < Denominator* other.Numerator;
}

bool Rational::operator>(const Rational& other) const {
    return other < *this;
}

bool Rational::operator>=(const Rational& other) const {
    return !(*this < other);
}

bool Rational::operator<=(const Rational& other) const {
    return !(*this > other);
}

bool Rational::operator==(const Rational& other) const {
    return Numerator == other.Numerator && Denominator == other.Denominator;
}

bool Rational::operator!=(const Rational& other) const {
    return !(*this == other);
}

void Rational::reduce() { 
    auto nod = gcd(Numerator < 0 ? -Numerator : Numerator, Denominator);
    if (nod != 1) {
        Numerator /= nod;
        Denominator /= nod;
    }
    if (Numerator < 0 && Denominator < 0) {
        Numerator = -Numerator;
        Denominator = -Denominator;
    }
    else if (Denominator < 0) {
        Numerator = -Numerator;
        Denominator = -Denominator;
    }
}

int Rational::gcd(int32_t a, int32_t b) const { 
    while (a) {
        auto t = b % a;
        b = a;
        a = t;
    }
    return b;
}

int main() {
    Rational x(10, 0);
}