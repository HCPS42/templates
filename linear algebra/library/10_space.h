#pragma once

#include <bits/stdc++.h>
#include "9_algo.h"
using namespace std;

template <class T>
struct Space {
    vector<Vec<T>> a;
    Space() = default;
    Space(const vector<vector<T>>& b) {
        a.resize(b.size());
        for (int i = 0; i < a.size(); i++) {
            a[i] = b[i];
        }
        reduce();
    }
    Space(const vector<Vec<T>>& b) {
        a = b;
        reduce();
    }
    Space(Mat<T> b) {
        gauss(b);
        a = b.a;
    }
    void reduce() {
        Mat<T> b(a);
        gauss(b);
        a = b.a;
    }
    int dim() const {
        return a.size();
    }
    vector<Vec<T>> get_basis() const {
        return a;
    }
    bool contains(Vec<T> b) const {
        int n = b.size();
        for (const Vec<T>& v : a) {
            int pivot;
            for (int i = 0; i < n; i++) {
                if (v[i] != T(0)) {
                    pivot = i;
                    break;
                }
            }
            if (b[pivot] == T(0)) {
                continue;
            }
            b -= b[pivot] * v;
        }
        return b == Vec<T>(n);
    }
    void add(const Vec<T>& b) {
        a.push_back(b);
        reduce();
    }
    Space& operator+=(const Space& b) {
        for (const Vec<T>& i : b.a) {
            add(i);
        }
        return *this;
    }
    friend Space operator+(Space a, const Space& b) {
        return a += b;
    }
    friend bool operator==(const Space& a, const Space& b) {
        return a.a == b.a;
    }
    friend ostream& operator<<(ostream& ou, const Space& b) {
        for (const Vec<T>& i : b.a) {
            ou << i << "\n";
        }
        return ou;
    }
    Mat<T> to_mat() const {
        return Mat<T>(a).t();
    }
    Space complement() const {
        assert(dim());
        int n = a[0].size();
        Mat<T> b = Mat<T>::I(n);
        Space space = *this;
        Space res;
        for (const Vec<T>& v : b.a) {
            if (!space.contains(v)) {
                space.add(v);
                res.add(v);
            }
        }
        return res;
    }
    Mat<T> projection(Space along) const {
        assert(dim());
        vector<Vec<T>> b = a;
        for (const Vec<T>& v : along.a) {
            b.push_back(v);
        }
        Mat<T> B(b);
        B = B.t();
        B = inverse(B);
        B = B.t();
        for (Vec<T>& v : B.a) {
            v.a.resize(dim());
        }
        B = B.t();
        return to_mat() * B;
    }
    Vec<T> project(const Vec<T>& b, Space along) const {
        assert(dim());
        return (projection(along) * b).to_vec();
    }
};

template <class T>
Space<T> image(const Mat<T>& a) {
    Space<T> res;
    for (int j = 0; j < a.cols(); j++) {
        Vec<T> b(a.rows());
        for (int i = 0; i < a.rows(); i++) {
            b[i] = a[i][j];
        }
        res.add(b);
    }
    return res;
}

template <class T>
Space<T> kernel(Mat<T> a) {
    gauss(a);
    int n = a.cols();
    set<int> pivots;
    vector<int> pivot(n, -1);
    for (int i = 0; i < a.rows(); i++) {
        const Vec<T>& v = a[i];
        for (int j = 0; j < n; j++) {
            if (v[j] != T(0)) {
                pivots.insert(j);
                pivot[j] = i;
                break;
            }
        }
    }
    Space<T> res;
    for (int j = 0; j < n; j++) {
        if (pivots.count(j)) {
            continue;
        }
        Vec<T> b(n);
        b[j] = 1;
        for (int p : pivots) {
            if (p > j) break;
            b[p] = -a[pivot[p]][j];
        }
        res.add(b);
    }
    return res;
}

template <class T>
Space<T> intersection(const Space<T>& U, const Space<T>& V) {
    if (!U.dim() || !V.dim()) {
        return {};
    }
    int n = U.a[0].size();
    int k = U.dim();
    Mat<T> A;
    for (const Vec<T>& i : U.a) {
        A.a.push_back(i);
    }
    for (const Vec<T>& i : V.a) {
        A.a.push_back(i);
    }
    A = A.t();
    Space<T> ker = kernel(A);
    Mat<T> U_mat = U.to_mat();
    for (Vec<T>& x : ker.a) {
        x.a.resize(k);
    }
    Space<T> res;
    for (const Vec<T>& x : ker.a) {
        res.add((U_mat * x).to_vec());
    }
    return res;
}
