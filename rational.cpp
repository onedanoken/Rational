#include <iostream>
#include "rational.h"

std::ostream& operator<<(std::ostream& out, const Rational& number) {
  out << number.numerator_;
  if (number.denominator_ != 1) {
    out << "/" << number.denominator_;
  }
  return out;
}

std::istream& operator>>(std::istream& in, Rational& number) {
  char separator;
  in >> number.numerator_ >> separator >> number.denominator_;
  number.Reduce();
  return in;
}

Rational::Rational() : numerator_(0), denominator_(1) {
}

Rational::Rational(int value) : numerator_(value), denominator_(1) {
}

Rational::Rational(int numerator, int denominator) : numerator_(numerator) {
  if (denominator == 0) {
    throw RationalDivisionByZero{};
  }
  denominator_ = denominator;
  Reduce();
}

void Rational::SetNumerator(int numerator) {
  numerator_ = numerator;
  Reduce();
}

int Rational::GetNumerator() const {
  return numerator_;
}

void Rational::SetDenominator(int denominator) {
  if (denominator == 0) {
    throw RationalDivisionByZero{};
  }
  denominator_ = denominator;
  Reduce();
}

int Rational::GetDenominator() const {
  return denominator_;
}

Rational Rational::operator=(int value) {
  numerator_ = value;
  denominator_ = 1;
  return *this;
}

Rational Rational::operator=(const Rational& other) {
  numerator_ = other.numerator_;
  denominator_ = other.denominator_;
  return *this;
}

Rational Rational::operator+(const Rational& other) const {
  int num = numerator_ * other.denominator_ + denominator_ * other.numerator_;
  int den = denominator_ * other.denominator_;
  return Rational{num, den};
}

Rational Rational::operator+=(const Rational& other) {
  return *this + other;
}

Rational Rational::operator-(const Rational& other) const {
  return -other + *this;
}

Rational Rational::operator-=(const Rational& other) {
  return *this - other;
}

Rational Rational::operator*(const Rational& other) const {
  return Rational(numerator_ * other.numerator_, denominator_ * other.denominator_);
}

Rational Rational::operator*=(const Rational& other) {
  return *this * other;
}

Rational Rational::operator/(const Rational& other) const {
  return Rational(numerator_ * other.denominator_, denominator_ * other.numerator_);
}

Rational Rational::operator/=(const Rational& other) {
  return *this / other;
}

Rational Rational::operator-() const {
  return Rational(-numerator_, denominator_);
}

Rational Rational::operator+() const {
  return Rational(numerator_, denominator_);
}

Rational operator+(const int& integer, const Rational& rational) {
  auto first = Rational(integer);
  return first + rational;
}

Rational operator-(const int& integer, const Rational& rational) {
  auto first = Rational(integer);
  return first - rational;
}

Rational operator*(const int& integer, const Rational& rational) {
  auto first = Rational(integer);
  return first * rational;
}

Rational operator/(const int& integer, const Rational& rational) {
  auto first = Rational(integer);
  return first / rational;
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
  return numerator_ * other.denominator_ < denominator_ * other.numerator_;
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
  return numerator_ == other.numerator_ && denominator_ == other.denominator_;
}

bool Rational::operator!=(const Rational& other) const {
  return !(*this == other);
}

bool operator==(const int& integer, const Rational& rational) {
  auto first = Rational(integer);
  return first == rational;
}

bool operator!=(const int& integer, const Rational& rational) {
  auto first = Rational(integer);
  return first != rational;
}

bool operator<(const int& integer, const Rational& rational) {
  auto first = Rational(integer);
  return first < rational;
}

bool operator>(const int& integer, const Rational& rational) {
  auto first = Rational(integer);
  return first > rational;
}

bool operator<=(const int& integer, const Rational& rational) {
  auto first = Rational(integer);
  return first <= rational;
}

bool operator>=(const int& integer, const Rational& rational) {
  auto first = Rational(integer);
  return first >= rational;
}

void Rational::Reduce() {
  auto nod = Gcd(numerator_ < 0 ? -numerator_ : numerator_, denominator_);
  if (nod != 1) {
    numerator_ /= nod;
    denominator_ /= nod;
  }
  if (denominator_ < 0 && numerator_ < 0) {
    numerator_ = -numerator_;
    denominator_ = -denominator_;
  } else if (denominator_ < 0) {
    numerator_ = -numerator_;
    denominator_ = -denominator_;
  }
}

int Rational::Gcd(int a, int b) const {
  while (a) {
    auto t = b % a;
    b = a;
    a = t;
  }
  return b;
}
