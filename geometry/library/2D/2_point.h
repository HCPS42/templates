#pragma once

#include "1_rational.h"

typedef int64_t Int;
typedef long double Real;

const Real eps = 1e-10;
const Real pi = acos(-1);

template <class T> T sq(T a) { return a * a; }
template <class T> bool zero(T a);
template <> bool zero<Int>(Int a) { return a == 0; }
template <> bool zero<Real>(Real a) { return abs(a) < eps; }
template <> bool zero<frac>(frac a) { return a == 0; }
template <class T> bool is_neg(T a);
template <> bool is_neg<Int>(Int a) { return a < 0; }
template <> bool is_neg<Real>(Real a) { return a < -eps; }
template <> bool is_neg<frac>(frac a) { return a < 0; }
template <class T> bool is_pos(T a);
template <> bool is_pos<Int>(Int a) { return a > 0; }
template <> bool is_pos<Real>(Real a) { return a > eps; }
template <> bool is_pos<frac>(frac a) { return a > 0; }
template <class T> bool is_eq(T a, T b) { return zero(a - b); }
template <class T> bool is_less(T a, T b) { return is_neg(a - b); }
template <class T> bool is_more(T a, T b) { return is_pos(a - b); }

template <class T>
struct Point {
    T x = 0;
    T y = 0;
    Point() = default;
    Point(T x, T y) : x(x), y(y) {}
    friend istream& operator>>(istream& in, Point& a) { return in >> a.x >> a.y; }
    friend ostream& operator<<(ostream& out, Point& a) { return out << a.x << " " << a.y; }
    Point operator-() const { return {-x, -y}; }
    Point& operator+=(const Point& a) { x += a.x; y += a.y; return *this; }
    Point& operator-=(const Point& a) { x -= a.x; y -= a.y; return *this; }
    Point& operator*=(const T& a) { x *= a; y *= a; return *this; }
    Point& operator/=(const T& a) { x /= a; y /= a; return *this; }
    friend Point operator+(Point a, const Point& b) { return a += b; }
    friend Point operator-(Point a, const Point& b) { return a -= b; }
    friend Point operator*(Point a, const T& b) { return a *= b; }
    friend Point operator*(const T& a, Point b) { return b *= a; }
    friend Point operator/(Point a, const T& b) { return a /= b; }
    bool is_zero() const { return zero(x) && zero(y); }
    bool operator==(const Point& a) const { return (*this - a).is_zero(); }
    bool operator!=(const Point& a) const { return !(*this == a); }
    friend bool operator<(const Point& a, const Point& b) {
        if (!is_eq(a.x, b.x)) return a.x < b.x; return a.y < b.y;
    }
    friend bool operator>(const Point& a, const Point& b) {
        if (!is_eq(a.x, b.x)) return a.x > b.x; return a.y > b.y;
    }
    friend bool operator<=(const Point& a, const Point& b) { return !(a > b); }
    friend bool operator>=(const Point& a, const Point& b) { return !(a < b); }
    friend T dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }
    friend T dot(const Point& a, const Point& b, const Point& c) { return dot(b - a, c - a); }
    friend T cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
    friend T cross (const Point& a, const Point& b, const Point& c) { return cross(b - a, c - a); }
    T norm2() const { return sq(x) + sq(y); }
    Real norm() const { return sqrt(Real(sq(x) + sq(y))); }
    void normalize_self() { *this /= norm(); }
    Point normalize() { Point a(*this); a.normalize_self(); return a; }
    friend T dist2(const Point& a, const Point& b) { return (a - b).norm2(); }
    friend Real dist(const Point& a, const Point& b) { return (a - b).norm(); }
    Real angle() { return atan2(y, x); }
    void rotate_self(Real ang) {
        if constexpr (std::is_same<Int, T>()) {
            Real c = cos(ang); Real s = sin(ang);
            Real nx = c * x - s * y; Real ny = s * x + c * y;
            x = round(nx); y = round(ny);
        }
        else if constexpr (std::is_same<Real, T>()) {
            Real c = cos(ang); Real s = sin(ang);
            Real nx = c * x - s * y; Real ny = s * x + c * y;
            x = nx; y = ny;
        }
        else {
            assert(0);
        }
    }
    Point rotate(Real ang) const {
        Point<T> a(*this);
        a.rotate_self(ang);
        return a;
    }
};
