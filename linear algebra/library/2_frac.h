#pragma once

#include <bits/stdc++.h>
#include "1_int.h"
using namespace std;

struct frac {
    Int x = 0;
    Int y = 1;
    void norm() {
        if (!y) {
            x = 1;
            return;
        }
        if (y < 0) {
            x *= -1;
            y *= -1;
        }
        Int d = __gcd(int64_t(x), int64_t(y));
        if (d < 0) d *= -1;
        x /= d;
        y /= d;
    }
    frac(int64_t x_ = 0, int64_t y_ = 1) : x(x_), y(y_) {
        norm();
    }
    friend istream& operator>>(istream& in, frac& a) {
        int64_t x;
        in >> x;
        a = {x, 1};
        return in;
    }
    friend ostream& operator<<(ostream& out, frac a) {
        return out << "(" << (int64_t(a.x) >= 0 ? " " : "-") <<
                   (to_string(abs(int64_t(a.x))).size() == 1 ? " " : "") << abs(int64_t(a.x)) << " / " <<
                   (to_string(abs(int64_t(a.y))).size() == 1 ? " " : "") << abs(int64_t(a.y)) << ")";
    }
    explicit operator long double() const { 
        return (long double) x / (long double) y;
    }
    frac operator-() const {
        return {int64_t(-x), int64_t(y)};
    }
    frac& operator+=(const frac& a) {
        x = x * a.y + a.x * y;
        y *= a.y;
        norm();
        return *this;
    }
    frac& operator-=(const frac& a) {
        x = x * a.y - a.x * y;
        y *= a.y;
        norm();
        return *this;
    }
    frac& operator*=(const frac& a) {
        x *= a.x;
        y *= a.y;
        norm();
        return *this;
    }
    frac& operator/=(const frac& a) {
        x *= a.y;
        y *= a.x;
        norm();
        return *this;
    }
    friend frac operator+(frac a, const frac& b) { return a += b; }
    friend frac operator-(frac a, const frac& b) { return a -= b; }
    friend frac operator*(frac a, const frac& b) { return a *= b; }
    friend frac operator/(frac a, const frac& b) { return a /= b; }
    friend bool operator==(const frac& a, const frac& b) { return a.x == b.x && a.y == b.y; }
    friend bool operator!=(const frac& a, const frac& b) { return !(a == b); }
    friend bool operator<(const frac& a, const frac& b) { return a.x * b.y < a.y * b.x; }
    friend bool operator>(const frac& a, const frac& b) { return b < a; }
    friend bool operator<=(const frac& a, const frac& b) { return !(a > b); }
    friend bool operator>=(const frac& a, const frac& b) { return !(a < b); }
    friend frac sq(frac x) { return x * x; }
    friend frac abs(frac x) {
        if (x < 0) {
            x = -x;
        }
        return x;
    }
};
