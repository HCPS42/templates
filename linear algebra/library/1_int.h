#pragma once

#include <bits/stdc++.h>
using namespace std;

struct Int {
    int64_t a = 0;
    Int(int64_t a_ = 0) : a(a_) {}
    friend ostream& operator<<(ostream& out, Int a) { return out << a.a; }
    explicit operator int64_t() const { return a; }
    explicit operator bool() const { return a; }
    explicit operator long double() const { return a; }
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
    friend Int operator+(Int a, const Int& b) { return a += b; }
    friend Int operator-(Int a, const Int& b) { return a -= b; }
    friend Int operator*(Int a, const Int& b) { return a *= b; }
    friend Int operator/(Int a, const Int& b) { return a /= b; }
    friend bool operator==(const Int& a, const Int& b) { return a.a == b.a; }
    friend bool operator!=(const Int& a, const Int& b) { return !(a == b); }
    friend bool operator<(const Int& a, const Int& b) { return a.a < b.a; }
    friend bool operator>(const Int& a, const Int& b) { return b < a; }
    friend bool operator<=(const Int& a, const Int& b) { return !(a > b); }
    friend bool operator>=(const Int& a, const Int& b) { return !(a < b); }
    friend Int abs(Int x) {
        if (x < 0) {
            x = -x;
        }
        return x;
    }
};
