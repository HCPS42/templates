#pragma once

#include <bits/stdc++.h>
using namespace std;

template <int m>
struct mint {
    int x = 0;
    mint(int64_t a = 0) {
        if (a < 0) {
            a = a % m + m;
        }
        if (a >= m) {
            a %= m;
        }
        x = a;
    }
    friend istream& operator>>(istream& in, mint& a) {
        int64_t y;
        cin >> y;
        a = y;
        return in;
    }
    friend ostream& operator<<(ostream& out, mint a) {
        return out << a.x;
    }
    explicit operator int() const {
        return x;
    }
    mint inv() const {
        return (*this).pow(m - 2);
    }
    friend mint binpow(mint a, int64_t b) {
        mint res = 1;
        while (b) {
            if (b & 1) {
                res *= a;
            }
            b >>= 1;
            a *= a;
        }
        return res;
    }
    mint pow(int64_t b) const {
        return binpow(*this, b);
    }
    mint operator-() const {
        return x ? m - x : 0;
    }
    mint& operator+=(const mint& a) {
        x += a.x;
        if (x >= m) {
            x -= m;
        }
        return *this;
    }
    mint& operator-=(const mint& a) {
        x -= a.x;
        if (x < 0) {
            x += m;
        }
        return *this;
    }
    mint& operator*=(const mint& a) {
        x = (int64_t) x * a.x % m;
        return *this;
    }
    mint& operator/=(const mint& a) {
        return *this *= a.inv();
    }
    friend mint operator+(mint a, const mint& b) { return a += b; }
    friend mint operator-(mint a, const mint& b) { return a -= b; }
    friend mint operator*(mint a, const mint& b) { return a *= b; }
    friend mint operator/(mint a, const mint& b) { return a /= b; }
    mint& operator++() {
        x = (x == m - 1) ? 0 : x + 1;
        return *this;
    }
    mint& operator--() {
        x = (x == 0) ? m - 1 : x - 1;
        return *this;
    }
    mint operator++(int) {
        mint a = *this;
        ++*this;
        return a;
    }
    mint operator--(int) {
        mint a = *this;
        --*this;
        return a;
    }
    bool operator==(const mint& a) const { return x == a.x; }
    bool operator!=(const mint& a) const { return x != a.x; }
    bool operator<(const mint& a) const { return x < a.x; }
    bool operator>(const mint& a) const { return x > a.x; }
    friend mint abs(const mint& a) { return a.x; }
};
