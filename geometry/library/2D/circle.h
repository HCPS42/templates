#pragma once

#include <bits/stdc++.h>
#include "point.h"
using namespace std;

template <class T>
struct Circle {
    Point cen;
    T r;
    Circle(T x, T y, T r) : cen(x, y), r(r) {}
    Real area() const { return pi * sq(r); }
    Real perimiter() const { return 2 * pi * r; }
    T diameter() const { return 2 * r; }
    Point rotate_rightmost(Real angle) {
        return cen + Point(r * cos(angle), r * sin(angle));
    }
    friend bool operator==(const Circle& a, const Circle& b) {
        return a.cen == b.cen && zero(a.r - b.r);
    }
};
