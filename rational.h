#pragma once
#include <stdexcept>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
 public:
  Rational();
  Rational(int value);  // NOLINT
  Rational(int numerator, int denominator);

  friend std::ostream& operator<<(std::ostream& out, const Rational& number);
  friend std::istream& operator>>(std::istream& in, Rational& number);

  void SetNumerator(int numerator);
  int GetNumerator() const;
  void SetDenominator(int denominator);
  int GetDenominator() const;

  Rational operator=(int value);
  Rational operator=(const Rational& other);
  Rational operator+(const Rational& other) const;
  Rational operator+=(const Rational& other);
  Rational operator-(const Rational& other) const;
  Rational operator-=(const Rational& other);
  Rational operator*(const Rational& other) const;
  Rational operator*=(const Rational& other);
  Rational operator/(const Rational& other) const;
  Rational operator/=(const Rational& other);
  Rational operator-() const;
  Rational operator+() const;

  friend Rational operator+(const int& integer, const Rational& rational);
  friend Rational operator-(const int& integer, const Rational& rational);
  friend Rational operator*(const int& integer, const Rational& rational);
  friend Rational operator/(const int& integer, const Rational& rational);

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

  friend bool operator==(const int& integer, const Rational& rational);
  friend bool operator!=(const int& integer, const Rational& rational);
  friend bool operator<(const int& integer, const Rational& rational);
  friend bool operator>(const int& integer, const Rational& rational);
  friend bool operator<=(const int& integer, const Rational& rational);
  friend bool operator>=(const int& integer, const Rational& rational);

 private:
  int numerator_;
  int denominator_;

  void Reduce();
  int Gcd(int a, int b) const;
};
