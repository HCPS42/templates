#include <bits/stdc++.h>
#include "permutation.h"
#include "modular.h"
#include "rational.h"
#include "complex.h"
#include "polynomial.h"
#include "vector.h"
#include "matrix.h"
#include "SLE.h"
#include "linear_algebraic_algorithms.h"
#include "space.h"
using namespace std;

Mat<frac> gen_rand_matrix() {
    if (rand() % 3 == 1) {
        Mat<frac> A({{
                             1, 2, 3, 4
                     }, {
                             4, 5, 6, 7
                     }, {
                             5, 6, 7, 8
                     }, {
                             6, 7, 8, 9
                     }});

        return A;
    }
    else if (rand() % 3 == 2) {
        vector<vector<frac>> a = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
        return a;
    }
    else {
        int n = 6;
        Mat<frac> A = Mat<frac>::Rand(n);
        return A;
    }
}

void test_perm() {
    perm a({2, 3, 4, 1});
    perm b({1, 3, 4, 2});
    cout << a.pow(-1) << endl;
    cout << a * b << endl;
}

void test_mint() {
    const int p = 1e9 + 7;
    mint<p> a = 10;
    mint<p> b = 10349;
    a += b;
    a -= b;
    a *= b;
    a /= b;
    cout << a << endl;
}

void test_frac() {
    frac a(100, 200);
    frac b(1, 17);
    frac c(14234);
    a += b;
    a -= b;
    a *= b;
    a /= b;
    cout << a << endl;
}

void test_poly() {
    poly<frac> a({1, 2, 3, 4});
    poly<frac> b({5, 6, 7, 8});
    a += b;
    a -= b;
    cout << a << endl;
    cout << b << endl;
    cout << a * b << endl;
}

void test_matrix() {
    Mat<frac> A = gen_rand_matrix();
    Mat<frac> B = gen_rand_matrix();
    cout << A + B << endl;
    cout << A - B << endl;
    cout << A * B << endl;
}

void test_algo() {
    Mat<frac> A = gen_rand_matrix();
    cout << det(A) << endl;
    if (det(A) != 0) {
        cout << inverse(A) << endl;
    }
    cout << char_poly(A) << endl;
    gauss(A);
    cout << A << endl;
}

void Solve() {
    test_perm();
    test_mint(); // just for fun, not actually necessary
    test_frac();
    test_poly();
    test_matrix();
    test_algo();
}

int main() {
    Solve();
    return 0;
}
