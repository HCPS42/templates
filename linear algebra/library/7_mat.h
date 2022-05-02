#pragma once

#include <bits/stdc++.h>
#include "6_vec.h"
using namespace std;

template <class T>
struct Mat {
    vector<Vec<T>> a;
    Mat() = default;
    Mat(int n, int m) { a.resize(n, m); }
    Mat(const vector<vector<T>>& b) {
        a.resize(b.size());
        for (int i = 0; i < a.size(); i++) {
            a[i] = b[i];
        }
    }
    Mat(const vector<Vec<T>>& b) : a(b) {}
    Mat(const Vec<T>& b) {
        a.resize(b.size(), 1);
        for (int i = 0; i < a.size(); i++) {
            a[i][0] = b[i];
        }
    }
    int rows() const { return a.size(); }
    int cols() const { return a[0].size(); }
    Vec<T>& operator[](int i) { return a[i]; }
    const Vec<T>& operator[](int i) const { return a[i]; }
    Vec<T> get_column(int j) const {
        Vec<T> res(rows());
        for (int i = 0; i < rows(); i++) {
            res[i] = a[i][j];
        }
        return res;
    }
    Mat& operator+=(const Mat& b) {
        for (int i = 0; i < rows(); i++) {
            a[i] += b[i];
        }
        return *this;
    }
    Mat& operator-=(const Mat& b) {
        for (int i = 0; i < rows(); i++) {
            a[i] -= b[i];
        }
        return *this;
    }
    Mat& operator*=(const Mat& b) {
        Mat c(rows(), b.cols());
        for (int i = 0; i < c.rows(); i++) {
            for (int j = 0; j < c.cols(); j++) {
                for (int k = 0; k < cols(); k++) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return *this = c;
    }
    Mat& operator*=(const T& b) {
        for (Vec<T>& i : a) {
            i *= b;
        }
        return *this;
    }
    friend Mat operator+(Mat a, const Mat& b) { return a += b; }
    friend Mat operator-(Mat a, const Mat& b) { return a -= b; }
    friend Mat operator*(Mat a, const Mat& b) { return a *= b; }
    friend Mat operator*(Mat a, const T& b) { return a *= b; }
    friend Mat operator*(const T& a, Mat b) { return b *= a; }
    friend bool operator==(const Mat& a, const Mat& b) {
        return a.a == b.a;
    }
    friend ostream& operator<<(ostream& ou, const Mat& b) {
        for (int i = 0; i < b.rows(); i++) {
            for (int j = 0; j < b.cols(); j++) {
                ou << b[i][j] << " ";
            }
            ou << "\n";
        }
        return ou;
    }
    Mat pow(int64_t n) const {
        Mat res = I(rows());
        Mat cur = *this;
        while (n) {
            if (n & 1) {
                res *= cur;
            }
            cur *= cur;
            n >>= 1;
        }
        return res;
    }
    Mat t() const {
        Mat b(cols(), rows());
        for (int i = 0; i < b.rows(); i++) {
            for (int j = 0; j < b.cols(); j++) {
                b[i][j] = a[j][i];
            }
        }
        return b;
    }
    Vec<T> to_vec() const {
        Vec<T> res;
        for (int i = 0; i < rows(); i++) {
            for (int j = 0; j < cols(); j++) {
                res.a.push_back(a[i][j]);
            }
        }
        return res;
    }
    static Mat I(int n) {
        Mat b(n, n);
        for (int i = 0; i < n; i++) {
            b[i][i] = 1;
        }
        return b;
    }
    static Mat O(int n, int m = -1) {
        if (m == -1) {
            return Mat(n, n);
        }
        return Mat(n, m);
    }
    static Mat Rand(int n, int m = -1) {
        if (m == -1) {
            m = n;
        }
        Mat res(n, m);
        random_device rd;
        mt19937 rnd(rd());
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res[i][j] = rnd() % 10;
            }
        }
        return res;
    }
};
