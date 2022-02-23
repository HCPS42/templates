#pragma once

#include <bits/stdc++.h>
#include "8_SLE.h"
#include "5_poly.h"
using namespace std;

template <class T>
void gauss(SLE<T>& sle) {
    Mat<T>& a = sle.a;
    Vec<T>& b = sle.b;
    int m = a.rows();
    int n = a.cols();
    int r = 0, c = 0;
    while (r < m && c < n) {
        T mx = 0;
        int id = r;
        for (int i = r; i < m; i++) {
            if (abs(a[i][c]) > abs(mx)) {
                mx = abs(a[i][c]);
                id = i;
            }
        }
        swap(a[id], a[r]);
        swap(b[id], b[r]);
        if (a[r][c] == T(0)) {
            c++;
            continue;
        }
        T pivot = a[r][c];
        for (int j = c; j < n; j++) {
            a[r][j] /= pivot;
        }
        b[r] /= pivot;
        for (int i = 0; i < m; i++) {
            if (i == r) continue;
            T coef = a[i][c];
            for (int j = c; j < n; j++) {
                a[i][j] -= coef * a[r][j];
            }
            b[i] -= coef * b[r];
        }
        r++;
        c++;
    }
    int sz = sle.rank();
    if (sz >= 0) {
        sle.a.a.resize(sz);
        sle.b.a.resize(sz);
    }
}

template <class T>
void gauss(Mat<T>& a) {
    Vec<T> b(a.cols());
    SLE<T> sle(a, b);
    gauss(sle);
    a = sle.a;
}

template <class T>
Mat<T> inverse(Mat<T> a) {
    int n = a.rows();
    Mat<T> b = Mat<T>::I(n);
    int r = 0, c = 0;
    while (r < n && c < n) {
        T mx = T(0);
        int id = r;
        for (int i = r; i < n; i++) {
            if (abs(a[i][c]) > abs(mx)) {
                mx = abs(a[i][c]);
                id = i;
            }
        }
        swap(a[id], a[r]);
        swap(b[id], b[r]);
        if (a[r][c] == T(0)) {
            c++;
            continue;
        }
        T pivot = a[r][c];
        for (int j = c; j < n; j++) {
            a[r][j] /= pivot;
        }
        b[r] /= pivot;
        for (int i = 0; i < n; i++) {
            if (i == r) continue;
            T coef = a[i][c];
            for (int j = c; j < n; j++) {
                a[i][j] -= coef * a[r][j];
            }
            b[i] -= coef * b[r];
        }
        r++;
        c++;
    }
    return b;
}

template <class T>
poly<T> char_poly_det(Mat<poly<T>> a) {
    int n = a.rows();
    if (n == 1) {
        return a[0][0];
    }
    poly<T> res;
    for (int i = 0; i < n; i++) {
        poly<T> cur = a[0][i];
        if (i & 1) {
            for (T& j : cur) {
                j *= -1;
            }
        }
        Mat<poly<T>> adj(n - 1, n - 1);
        for (int j = 1; j < n; j++) {
            int c = 0;
            for (int k = 0; k < n; k++) {
                if (k == i) continue;
                adj[j - 1][c] = a[j][k];
                c++;
            }
        }
        char_poly_det(adj);
        cur *= char_poly_det(adj);
        res += cur;
    }
    return res;
}

template <class T>
poly<T> char_poly(Mat<T> a) {
    // det(x I - A)
    int n = a.rows();
    Mat<poly<T>> b(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                b[i][j] = vector<T>{-a[i][j], 1};
            }
            else {
                b[i][j] = vector<T>{-a[i][j]};
            }
        }
    }
    return char_poly_det(b);
}

template <class T>
T det(Mat<T> a) {
    return (a.rows() % 2 == 1 ? -1 : 1) * char_poly(a)[0];
}
