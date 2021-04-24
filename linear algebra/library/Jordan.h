#include <bits/stdc++.h>
#include "rational.h"
#include "vector.h"
#include "matrix.h"
#include "linear_algebraic_algorithms.h"
#include "space.h"
using namespace std;

template <class T>
int num_of_blocks(Mat<T> A, T lambda, int size) {
    Mat<T> I = Mat<T>::I(A.rows());
    return 2 * kernel((A - lambda * I).pow(size)).dim()
        - kernel((A - lambda * I).pow(size - 1)).dim()
        - kernel((A - lambda * I).pow(size + 1)).dim();
}

template <class T>
vector<pair<T, int>> Jordan_blocks(Mat<T> A, vector<T> roots = {}) {
    if (roots.empty()) {
        roots = find_roots(char_poly(A));
    }
    vector<pair<T, int>> blocks;
    for (T lambda : roots) {
        for (int size = 1; size <= A.rows(); size++) {
            int num = num_of_blocks(A, lambda, size);
            for (int i = 1; i <= num; i++) {
                blocks.push_back({lambda, size});
            }
        }
    }
    sort(blocks.begin(), blocks.end());
    return blocks;
}

template <class T>
pair<Mat<T>, Mat<T>> Jordan_decomposition(Mat<T> A, vector<T> roots = {}) {
    // A = P J P^{-1}
    if (roots.empty()) {
        roots = find_roots(char_poly(A));
    }
    Mat<T> P;
    for (T lambda : roots) {
        Mat<T> B = A - lambda * Mat<T>::I(A.rows());
        int k = 1;
        while (kernel(B.pow(k)).dim() < kernel(B.pow(k + 1)).dim()) {
            k++;
        }
        vector<vector<Vec<T>>> table(k + 1);
        for (int i = k; i >= 1; i--) {
            Space<T> U = kernel(B.pow(i));
            Space<T> W = kernel(B.pow(i - 1));
            Space<T> cur = W;
            for (Vec<T> x : table[i]) {
                cur.add(x);
            }
            vector<Vec<T>> extension;
            for (Vec<T> x : U.get_basis()) {
                if (!cur.contains(x)) {
                    cur.add(x);
                    extension.push_back(x);
                }
            }
            for (Vec<T> x : extension) {
                table[i].push_back(x);
            }
            for (Vec<T> x : table[i]) {
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
    Mat<T> J = inverse(P) * A * P;
    assert(A == P * J * inverse(P));
    return {P, J};
}

template <class T>
Mat<T> Jordan_form(Mat<T> A, vector<T> roots = {}) {
    return Jordan_decomposition(A, roots).second;
}
