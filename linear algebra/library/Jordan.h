#include <bits/stdc++.h>
#include "rational.h"
#include "vector.h"
#include "matrix.h"
#include "linear_algebraic_algorithms.h"
#include "space.h"
using namespace std;

int num_of_cells(Mat<frac> A, frac lambda, int size) {
    int n = A.rows();
    Mat<frac> I = Mat<frac>::I(n);
    return 2 * kernel((A - lambda * I).pow(size)).dim()
        - kernel((A - lambda * I).pow(size - 1)).dim()
        - kernel((A - lambda * I).pow(size + 1)).dim();
}

void jordan_form(Mat<frac> A, vector<frac> roots = {}) {
    //out(char_poly(A));
    for (frac lambda : roots) {
        for (int size = 1; size <= A.rows(); size++) {
            int num = num_of_cells(A, lambda, size);
            if (num) {
                //out(lambda, size, num);
            }
        }
    }
}

void jordan_decomposition(Mat<frac> A, vector<frac> roots = {}) {
    // A = P J P^{-1}
    Mat<frac> P;
    for (frac lambda : roots) {
        Mat<frac> B = A - lambda * Mat<frac>::I(A.rows());
        int k = 1;
        while (kernel(B.pow(k)).dim() < kernel(B.pow(k + 1)).dim()) {
            k++;
        }
        vector<vector<Vec<frac>>> table(k + 1);
        for (int i = k; i >= 1; i--) {
            Space<frac> U = kernel(B.pow(i));
            Space<frac> W = kernel(B.pow(i - 1));
            Space<frac> cur = W;
            for (Vec<frac> x : table[i]) {
                cur.add(x);
            }
            vector<Vec<frac>> extension;
            for (Vec<frac> x : U.get_basis()) {
                if (!cur.contains(x)) {
                    cur.add(x);
                    extension.push_back(x);
                }
            }
            for (Vec<frac> x : extension) {
                table[i].push_back(x);
            }
            for (Vec<frac> x : table[i]) {
                table[i - 1].push_back((B * x).to_vec());
            }
        }
        for (int i = 0; i < table[1].size(); i++) {
            for (int j = 1; j <= k; j++) {
                if (table[j].size() <= i) break;
                P.a.push_back(table[j][i]);
            }
        }
    }
    P = P.t();
    Mat<frac> J = inverse(P) * A * P;
    //out(P);
    //out(J);
    assert(A == P * J * inverse(P));
}

void task_1() {
    Mat<frac> A({{7, -4},
                 {14, -8}});
    jordan_form(A, {0, -1});
    Mat<frac> P({{4, 1},
                 {7, 2}});
    //out(inverse(P) * A * P);
    //out(P * Mat<frac>({{0, 0}, {0, 1}}) * inverse(P));
}

void task_2_a() {
    Mat<frac> A({{5, -7, -4},
                 {6, -9, -5},
                 {-6, 8, 4}});
    jordan_decomposition(A, {-1, 2});
}

void task_2_b() {
    Mat<frac> A({{5, -2, -1},
                 {9, -4, -3},
                 {-9, 6, 5}});
    jordan_decomposition(A, {2});
}

void task_2_c() {
    Mat<frac> A({{1, -3, 0, 3},
                 {-2, -6, 0, 13},
                 {0, -3, 1, 3},
                 {-1, -4, 0, 8}});
    jordan_decomposition(A, {1});
}

void task_2_d() {
    Mat<frac> A({{3, -1, 1, -7},
                 {9, -3, -7, -1},
                 {0, 0, 4, -8},
                 {0, 0, 2, -4}});
    jordan_decomposition(A, {0});
}
