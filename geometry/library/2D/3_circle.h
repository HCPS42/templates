#pragma once

#include "2_point.h"

template <class T>
struct Circle {
    Point<T> cen;
    T r = 0;
    Circle() = default;
    Circle(T x, T y, T r) : cen(x, y), r(r) {}
    Circle(Point<T> cen, T r) : cen(cen), r(r) {}
    friend istream& operator>>(istream& in, Circle& a) { return in >> a.cen >> a.r; }
    friend ostream& operator<<(ostream& out, Circle& a) { return out << a.cen << " " << a.r; }
    Real area() const { return pi * sq(r); }
    Real perimeter() const { return 2 * pi * r; }
    T diameter() const { return 2 * r; }
    Point<Real> rotate_rightmost(Real angle) {
        return Point<Real>(cen.x, cen.y) + Point<Real>(r * cos(angle), r * sin(angle));
    }
    friend bool operator==(const Circle& a, const Circle& b) {
        return a.cen == b.cen && is_eq(a.r, b.r);
    }
};
