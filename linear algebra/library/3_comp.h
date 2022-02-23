#pragma once

#include <bits/stdc++.h>
using namespace std;

typedef long double Real;

template <class T>
struct Comp {
    T x;
    T y;
    Comp(T x_ = 0, T y_ = 0) : x(x_), y(y_) {}
    Real real() const { return x; }
    Real imag() const { return y; }
    Comp conj() const { return {x, -y}; }
    T norm2() const { return x * x + y * y; }
    Real norm() const { return sqrt((Real) norm2()); }
    Comp operator-() const { return {-x, -y}; }
    Comp& operator+=(const Comp& a) {
        x += a.x;
        y += a.y;
        return *this;
    }
    Comp& operator-=(const Comp& a) {
        x -= a.x;
        y -= a.y;
        return *this;
    }
    Comp& operator*=(const Comp& a) {
        T new_x = x * a.x - y * a.y;
        T new_y = x * a.y + y * a.x;
        x = new_x;
        y = new_y;
        return *this;
    }
    Comp& operator/=(const Comp& a) {
        *this *= a.conj();
        T b = a.norm2();
        x /= b;
        y /= b;
        return *this;
    }
    friend Comp operator+(Comp a, const Comp& b) { return a += b; }
    friend Comp operator-(Comp a, const Comp& b) { return a -= b; }
    friend Comp operator*(Comp a, const Comp& b) { return a *= b; }
    friend Comp operator/(Comp a, const Comp& b) { return a /= b; }
    friend bool operator==(const Comp& a, const Comp& b) {
        return a.x == b.x && a.y == b.y;
    }
    friend bool operator!=(const Comp& a, const Comp& b) {
        return !(a == b);
    }
    friend Real abs(const Comp& a) {
        return a.norm();
    }
};
