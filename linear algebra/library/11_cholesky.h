#pragma once

#include <bits/stdc++.h>
#include "9_algo.h"
#include "3_comp.h"
using namespace std;

Mat<Real> cholesky_decomposition(Mat<Real> A) {
    // A \in \R^{n \times n}
    // A = L L^T
    // result = L
    // L --- lower triangular
    // O(n^3)
    Mat<Real> L(A.rows(), A.cols());
    Real a = A[0][0];
    Real l = sqrt(a);
    cout << "a: " << a << endl;
    L[0][0] = l;
    if (A.rows() == 1) {
        return L;
    }
    for (int i = 1; i < A.rows(); ++i) {
        L[i][0] = A[i][0] / l;
        L[i][i] = 1;
    }
    Mat<Real> D(A.rows() - 1, A.cols() - 1);
    for (int i = 1; i < A.rows(); ++i) {
        for (int j = 1; j < A.cols(); ++j) {
            D[i - 1][j - 1] = A[i][j] - (A[i][0] * A[j][0]) / a;
        }
    }
    cout << "D:\n" << D << endl;
    D = cholesky_decomposition(D);
    Mat<Real> F(A.rows(), A.cols());
    F[0][0] = 1;
    for (int i = 1; i < A.rows(); ++i) {
        for (int j = 1; j < A.cols(); ++j) {
            F[i][j] = D[i - 1][j - 1];
        }
    }
    cout << "L:\n" << L << endl;
    cout << "F:\n" << F << endl;
    L *= F;
    //assert(L * L.t() == A);
    cout << "L:\n" << L << endl;
    return L;
}
