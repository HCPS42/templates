#pragma once

#include <bits/stdc++.h>
using namespace std;

template <class T>
struct Vec {
    vector<T> a;
    Vec() = default;
    Vec(int n) {
        a.resize(n, T(0));
    }
    Vec(const vector<T>& b) : a(b) {
    }
    int size() const {
        return a.size();
    }
    T& operator[](int i) {
        return a[i];
    }
    const T& operator[](int i) const {
        return a[i];
    }
    Vec& operator+=(const Vec& b) {
        for (int i = 0; i < size(); i++) {
            a[i] += b[i];
        }
        return *this;
    }
    Vec& operator-=(const Vec& b) {
        for (int i = 0; i < size(); i++) {
            a[i] -= b[i];
        }
        return *this;
    }
    Vec& operator*=(const T& b) {
        for (int i = 0; i < size(); i++) {
            a[i] *= b;
        }
        return *this;
    }
    Vec& operator/=(const T& b) {
        for (int i = 0; i < size(); i++) {
            a[i] /= b;
        }
        return *this;
    }
    friend Vec operator+(Vec a, const Vec& b) {
        return a += b;
    }
    friend Vec operator-(Vec a, const Vec& b) {
        return a -= b;
    }
    friend Vec operator*(Vec a, const T& b) {
        return a *= b;
    }
    friend Vec operator*(const T& a, Vec b) {
        return b *= a;
    }
    friend Vec operator/(Vec a, const T& b) {
        return a /= b;
    }
    friend bool operator==(const Vec& a, const Vec& b) {
        return a.a == b.a;
    }
    friend ostream& operator<<(ostream& ou, const Vec& b) {
        ou << "(";
        for (int i = 0; i < b.size(); i++) {
            if (i) ou << ", ";
            ou << b[i];
        }
        ou << ")";
        return ou;
    }
    friend T operator*(const Vec& a, const Vec& b) {
        T res(0);
        for (int i = 0; i < a.size(); i++) {
            res += a[i] * b[i];
        }
        return res;
    }
};

template <class T>
ostream& operator<<(ostream& out, const vector<Vec<T>>& a) {
    for (const Vec<T>& i : a) {
        out << i << endl;
    }
    return out;
}
