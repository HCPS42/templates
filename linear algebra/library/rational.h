#pragma once

#include <bits/stdc++.h>
using namespace std;

struct Int {
    int64_t a = 0;
    Int(int64_t a_ = 0) : a(a_) {}
    friend ostream& operator<<(ostream& out, Int a) {
        return out << a.a;
    }
    explicit operator int64_t() const {
        return a;
    }
    explicit operator bool() const {
        return a;
    }
    Int operator-() const {
        assert(a != numeric_limits<int64_t>::min());
        return {-a};
    }
    Int& operator+=(const Int& x) {
        int64_t b = x.a;
        assert(!(b > 0 && a > numeric_limits<int64_t>::max() - b));
        assert(!(b < 0 && a < numeric_limits<int64_t>::min() - b));
        a += b;
        return *this;
    }
    Int& operator-=(const Int& x) {
        int64_t b = x.a;
        assert(!(b < 0 && a > numeric_limits<int64_t>::max() + b));
        assert(!(b > 0 && a < numeric_limits<int64_t>::min() + b));
        a -= b;
        return *this;
    }
    Int& operator*=(const Int& x) {
        int64_t b = x.a;
        assert(!(a > 0 && b > 0 && a > numeric_limits<int64_t>::max() / b));
        assert(!(a < 0 && b > 0 && a < numeric_limits<int64_t>::min() / b));
        assert(!(a > 0 && b < 0 && b < numeric_limits<int64_t>::min() / a));
        assert(!(a < 0 && b < 0 && (a <= numeric_limits<int64_t>::min()
                                    || b <= numeric_limits<int64_t>::min()
                                    || -a > numeric_limits<int64_t>::max() / -b)));
        a *= b;
        return *this;
    }
    Int& operator/=(const Int& x) {
        int64_t b = x.a;
        assert(!(a == numeric_limits<int64_t>::min() && b == -1));
        a /= b;
        return *this;
    }
    friend Int operator+(Int a, const Int& b) {
        return a += b;
    }
    friend Int operator-(Int a, const Int& b) {
        return a -= b;
    }
    friend Int operator*(Int a, const Int& b) {
        return a *= b;
    }friend Int operator/(Int a, const Int& b) {
        return a /= b;
    }
    friend bool operator==(const Int& a, const Int& b) {
        return a.a == b.a;
    }
    friend bool operator!=(const Int& a, const Int& b) {
        return !(a == b);
    }
    friend bool operator<(const Int& a, const Int& b) {
        return a.a < b.a;
    }
    friend bool operator>(const Int& a, const Int& b) {
        return b < a;
    }
    friend bool operator<=(const Int& a, const Int& b) {
        return !(a > b);
    }
    friend bool operator>=(const Int& a, const Int& b) {
        return !(a < b);
    }
    friend Int abs(Int x) {
        if (x < 0) {
            x *= -1;
        }
        return x;
    }
};

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
    friend frac operator+(frac a, const frac& b) {
        return a += b;
    }
    friend frac operator-(frac a, const frac& b) {
        return a -= b;
    }
    friend frac operator*(frac a, const frac& b) {
        return a *= b;
    }
    friend frac operator/(frac a, const frac& b) {
        return a /= b;
    }
    friend bool operator==(const frac& a, const frac& b) {
        return a.x == b.x && a.y == b.y;
    }
    friend bool operator!=(const frac& a, const frac& b) {
        return !(a == b);
    }
    friend bool operator<(const frac& a, const frac& b) {
        return a.x * b.y < a.y * b.x;
    }
    friend bool operator>(const frac& a, const frac& b) {
        return b < a;
    }
    friend bool operator<=(const frac& a, const frac& b) {
        return !(a > b);
    }
    friend bool operator>=(const frac& a, const frac& b) {
        return !(a < b);
    }
    friend frac sq(frac x) {
        return x * x;
    }
    friend frac abs(frac x) {
        if (x < 0) {
            x *= -1;
        }
        return x;
    }
};
