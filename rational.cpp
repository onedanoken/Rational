#include <iostream>
#include <numeric>
#include "rational.h"
#include <string>

std::ostream& operator<<(std::ostream& out, const Rational& number) {
  if (number.denominator_ == 1) {
    out << number.numerator_;
  } else {
    out << number.numerator_ << "/" << number.denominator_;
  }
  return out;
}

std::istream& operator>>(std::istream& in, Rational& number) {
  std::string str;
  in >> str;
  auto slash = str.find('/');
  if (slash != std::string::npos) {
    number = Rational(std::stoi(str.substr(0, slash)), std::stoi(str.substr(slash + 1, str.size() - slash - 1)));
  } else {
    number.numerator_ = std::stoi(str);
    number.denominator_ = 1;
  }
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

void Rational::SetNumerator(const int& numerator) {
  numerator_ = numerator;
  Reduce();
}

int Rational::GetNumerator() const {
  return numerator_;
}

void Rational::SetDenominator(const int& denominator) {
  if (denominator == 0) {
    throw RationalDivisionByZero{};
  }
  denominator_ = denominator;
  Reduce();
}

int Rational::GetDenominator() const {
  return denominator_;
}

Rational Rational::operator+(const Rational& other) const {
  int num = numerator_ * other.denominator_ + denominator_ * other.numerator_;
  int den = denominator_ * other.denominator_;
  return Rational{num, den};
}

Rational& Rational::operator+=(const Rational& other) {
  *this = *this + other;
  return *this;
}

Rational Rational::operator-(const Rational& other) const {
  int num = numerator_ * other.denominator_ - denominator_ * other.numerator_;
  int den = denominator_ * other.denominator_;
  return Rational{num, den};
}

Rational& Rational::operator-=(const Rational& other) {
  *this = *this - other;
  return *this;
}

Rational Rational::operator*(const Rational& other) const {
  return Rational(numerator_ * other.numerator_, denominator_ * other.denominator_);
}

Rational& Rational::operator*=(const Rational& other) {
  *this = *this * other;
  return *this;
}

Rational Rational::operator/(const Rational& other) const {
  return Rational{numerator_ * other.denominator_, denominator_ * other.numerator_};
}

Rational& Rational::operator/=(const Rational& other) {
  *this = *this / other;
  return *this;
}

Rational Rational::operator-() const {
  return Rational{-numerator_, denominator_};
}

Rational Rational::operator+() const {
  return *this;
}

Rational operator+(const int& integer, const Rational& rational) {
  return Rational(integer) + rational;
}

Rational operator-(const int& integer, const Rational& rational) {
  return Rational(integer) - rational;
}

Rational operator*(const int& integer, const Rational& rational) {
  return Rational(integer) * rational;
}

Rational operator/(const int& integer, const Rational& rational) {
  return Rational(integer) / rational;
}

Rational& Rational::operator++() {
  *this = *this + 1;
  return *this;
}

Rational Rational::operator++(int) {
  Rational before = *this;
  operator++();
  return before;
}

Rational& Rational::operator--() {
  *this = *this - 1;
  return *this;
}

Rational Rational::operator--(int) {
  Rational before = *this;
  operator--();
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
  return Rational{integer} == rational;
}

bool operator!=(const int& integer, const Rational& rational) {
  return Rational{integer} != rational;
}

bool operator<(const int& integer, const Rational& rational) {
  return Rational{integer} < rational;
}

bool operator>(const int& integer, const Rational& rational) {
  auto first = Rational{integer};
  return first > rational;
}

bool operator<=(const int& integer, const Rational& rational) {
  return Rational{integer} <= rational;
}

bool operator>=(const int& integer, const Rational& rational) {
  return Rational{integer} >= rational;
}

void Rational::Reduce() {
  auto nod = std::gcd(numerator_, denominator_);
  if (nod != 1) {
    numerator_ /= nod;
    denominator_ /= nod;
  }
  if (denominator_ < 0) {
    numerator_ = -numerator_;
    denominator_ = -denominator_;
  }
}
