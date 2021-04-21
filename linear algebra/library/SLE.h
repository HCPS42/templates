#pragma once

#include <bits/stdc++.h>
#include "vector.h"
#include "matrix.h"
using namespace std;

template <class T>
struct SLE {
    Mat<T> a;
    Vec<T> b;
    SLE() = default;
    SLE(const Mat<T>& a, const Vec<T>& b) : a(a), b(b) {}
    friend bool operator==(const SLE& a, const SLE& b) {
        return a.a == b.a && a.b == b.b;
    }
    int rows() const {
        return a.rows();
    }
    int cols() const {
        return a.cols();
    }
    int rank() const {
        // assumes that the SLE is in the RREF
        int res = 0;
        for (int i = 0; i < rows(); i++) {
            bool non_zero = 0;
            for (int j = 0; j < cols(); j++) {
                if (a[i][j] != T(0)) {
                    non_zero = 1;
                    break;
                }
            }
            if (non_zero) res++;
            else if (b[i] != T(0)) {
                return -1;
            }
        }
        return res;
    }
    friend ostream& operator<<(ostream& ou, const SLE& sle) {
        ou << "rank: " << sle.rank();
        if (sle.rank() == -1) {
            ou << " (inconsistent system)";
        }
        ou << "\n";
        for (int i = 0; i < sle.rows(); i++) {
            for (int j = 0; j < sle.cols(); j++) {
                ou << sle.a[i][j] << " ";
            }
            ou << "| " << sle.b[i] << "\n";
        }
        return ou;
    }
};
