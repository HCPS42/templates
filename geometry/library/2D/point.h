#pragma once

#include <bits/stdc++.h>
#include "rational.h"
using namespace std;

typedef int64_t Int;
typedef long double Real;

const Real eps = 1e-8;
const Real inf = 1e18 + 5;
const Real pi = acos(-1);

template <class T> T sq(T a) { return a * a; }
template <class T> bool zero(T a);
template <> bool zero<Int>(Int a) { return a == 0; }
template <> bool zero<Real>(Real a) { return abs(a) < eps; }
template <> bool zero<frac>(frac a) { return a == 0; }

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
    bool is_zero() const { return zero<T>(x) && zero<T>(y); }
    bool operator==(const Point& a) const { return (*this - a).is_zero(); }
    bool operator!=(const Point& a) const { return !(*this == a); }
    friend bool operator<(const Point& a, const Point& b) {
        if (!zero(a.x - b.x)) return a.x < b.x; return a.y < b.y;
    }
    friend bool operator>(const Point& a, const Point& b) {
        if (!zero(a.x - b.x)) return a.x > b.x; return a.y > b.y;
    }
    friend T dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }
    friend T dot(const Point& a, const Point& b, const Point& c) { return dot(b - a, c - a); }
    friend T cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
    friend T cross (const Point& a, const Point& b, const Point& c) { return cross(b - a, c - a); }
    T norm2() const { return sq(x) + sq(y); }
    Real norm() const { return sqrt(Real(sq(x) + sq(y))); }
    void normalize_self() { *this /= norm(); }
    Point normalize() { Point res(*this); res.normalize_self(); return res; }
    friend T dist2(Point a, const Point& b) { return (a - b).norm2(); }
    friend Real dist(Point a, const Point& b) { return (a - b).norm(); }
    Real angle() { return atan2(y, x); }
    void rotate_self(Real angle) {
        Real c = cos(angle); Real s = sin(angle);
        Real nx = c * x - s * y; Real ny = s * x + c * y;
        x = nx; y = ny;
    }
    Point rotate(Real angle) const { Point res(*this); res.rotate_self(angle); return res; }
};
