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

void Solve() {
    Vec<frac> v_1({-3, 3, 5, 2, 1, -1});
    Vec<frac> v_2({2, -1, -7, 1, -3, 2});
    Mat<frac> A({{
                         2, -2, 3, 1, -4, 1
                 }, {
                         1, -1, -1, 3, 3, -2
                 }, {
                         -1, 1, 3, -5, -7, 4
                 }});
    cout << A * v_1 << endl;
    cout << A * v_2 << endl;
    Space<frac> space;
    space.add(v_1);
    space.add(v_2);
    Space<frac> ker = kernel(A);
    vector<Vec<frac>> answer;
    for (Vec<frac> v : ker.a) {
        if (!space.contains(v)) {
            answer.push_back(v);
            space.add(v);
        }
    }
    assert(space == ker);
    cout << answer.size() << endl;
    for (Vec<frac> v : answer) {
        cout << v << endl;
    }
}

/*

Output:

(  0 /  1) 
(  0 /  1) 
(  0 /  1) 

(  0 /  1) 
(  0 /  1) 
(  0 /  1) 

2
((  1 /  1), (  0 /  1), (  0 /  1), (  0 /  1), (  1 /  1), (  2 /  1))
((  0 /  1), (  1 /  1), (  0 /  1), (  0 /  1), (- 1 /  1), (- 2 /  1))

*/

int main() {
    Solve();
    return 0;
}
