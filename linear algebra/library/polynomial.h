#pragma once

#include <bits/stdc++.h>
using namespace std;

template <class T>
struct poly {
    vector<T> a;
    void trim() {
        while (!a.empty() && a.back() == T(0)) {
            a.pop_back();
        }
    }
    poly() = default;
    explicit poly(const vector<T>& b) : a(b) {
        trim();
    }
    explicit poly(const T& b) {
        a.push_back(b);
        trim();
    }
    template <class Iter>
    poly(Iter first, Iter last) {
        while (first != last) {
            a.push_back((*first)++);
        }
        trim();
    }
    explicit poly(initializer_list<T> l) : a(l) {
        trim();
    }
    int deg() const {
        if (a.empty()) {
            return -1;
        }
        return a.size() - 1;
    }
    typename vector<T>::iterator begin() {
        return a.begin();
    }
    typename vector<T>::iterator end() {
        return a.end();
    }
    poly<T>& operator=(const vector<T>& b) {
        a = b;
        trim();
        return *this;
    }
    T operator[](int i) const {
        if (i < 0 || deg() < i) {
            return T(0);
        }
        return a[i];
    }
    poly& operator+=(const poly& b) {
        while (deg() < b.deg()) {
            a.push_back(T(0));
        }
        for (int i = 0; i <= b.deg(); ++i) {
            a[i] += b[i];
        }
        trim();
        return *this;
    }
    poly& operator+=(const T& b) {
        return *this += poly(b);
    }
    poly& operator-=(const poly& b) {
        while (deg() < b.deg()) {
            a.push_back(T(0));
        }
        for (int i = 0; i <= b.deg(); ++i) {
            a[i] -= b[i];
        }
        trim();
        return *this;
    }
    poly& operator-=(const T& b) {
        return *this -= poly(b);
    }
    poly& operator*=(const poly& b) {
        if (deg() == -1) {
            return *this;
        }
        vector<T> prod(deg() + b.deg() + 1, T(0));
        for (int i = 0; i <= deg(); ++i) {
            for (int j = 0; j <= b.deg(); ++j) {
                prod[i + j] += a[i] * b[j];
            }
        }
        return *this = poly(prod);
    }
    poly& operator*=(const T& b) {
        return *this *= poly(b);
    }
    friend poly operator+(poly lhs, const poly& rhs) {
        return lhs += rhs;
    }
    friend poly operator+(poly lhs, const T& rhs) {
        return lhs += rhs;
    }
    friend poly operator+(const T& lhs, poly rhs) {
        return rhs += lhs;
    }
    friend poly operator-(poly lhs, const poly& rhs) {
        return lhs -= rhs;
    }
    friend poly operator-(poly lhs, const T& rhs) {
        return lhs -= rhs;
    }
    friend poly operator-(const T& lhs, poly rhs) {
        return rhs -= lhs;
    }
    friend poly operator*(poly lhs, const poly& rhs) {
        return lhs *= rhs;
    }
    friend poly operator*(poly lhs, const T& rhs) {
        return lhs *= rhs;
    }
    friend poly operator*(const T& lhs, poly rhs) {
        return rhs *= lhs;
    }
    friend bool operator==(const poly& lhs, const poly& rhs) {
        return lhs.a == rhs.a;
    }
    friend bool operator==(const poly& lhs, const T& rhs) {
        return lhs == poly(rhs);
    }
    friend bool operator==(const T& lhs, const poly& rhs) {
        return rhs == lhs;
    }
    friend bool operator!=(const poly& lhs, const poly& rhs) {
        return !(lhs == rhs);
    }
    friend bool operator!=(const poly& lhs, const T& rhs) {
        return !(lhs == rhs);
    }
    friend bool operator!=(const T& lhs, const poly& rhs) {
        return !(rhs == lhs);
    }
    poly pow(int64_t b) {
        poly res(1);
        poly cur = *this;
        while (b) {
            if (b & 1) {
                res *= cur;
            }
            cur *= *this;
            b >>= 1;
        }
        return res;
    }
};

template <class T>
ostream& operator<<(ostream& out, const poly<T>& a) {
    if (a.deg() == -1) {
        return out << "0";
    }
    for (int i = a.deg(); i >= 0; --i) {
        const T& c = a[i];
        if (c == T(0)) {
            continue;
        }
        if (i != a.deg()) {
            out << " + ";
        }
        out << c;
        if (i > 1) {
            out << " x^{" << i << "}";
        }
        else if (i == 1) {
            out << " x";
        }
    }
    return out;
}
