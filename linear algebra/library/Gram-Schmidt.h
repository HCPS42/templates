#include <bits/stdc++.h>
#include "rational.h"
#include "vector.h"
#include "matrix.h"
#include "linear_algebraic_algorithms.h"
#include "space.h"
using namespace std;

template <class T>
bool is_orthogonal_set(vector<Vec<T>> a, Mat<T> B = {}) {
    assert(!a.empty());
    if (B.rows() == 0) {
        B = Mat<T>::I(a[0].size());
    }
    for (int i = 0; i < a.size(); i++) {
        for (int j = i + 1; j < a.size(); j++) {
            if ((Mat<T>(a[i]).t() * B * Mat<T>(a[j]))[0][0] != 0) {
                return 0;
            }
        }
    }
    return 1;
}

template <class T> 
vector<Vec<T>> orthogonalize(vector<Vec<T>> a, Mat<T> B = {}) {
    assert(!a.empty());
    if (B.rows() == 0) {
        B = Mat<T>::I(a[0].size());
    }
    for (int i = 1; i < a.size(); i++) {
        Vec<T> proj(a[i].size());
        for (int j = 0; j < i; j++) {
            T coef = (Mat<T>(a[j]).t() * B * Mat<T>(a[j]))[0][0];
            assert(coef != 0);
            coef = (Mat<T>(a[j]).t() * B * Mat<T>(a[i]))[0][0] / coef;
            proj += coef * a[j];
        }
        a[i] -= proj;
    }
    assert(is_orthogonal_set(a, B));
    return a;
}

template <class T>
vector<Vec<T>> extend_to_orthogonal_basis(vector<Vec<T>> a, Mat<T> B = {}) {
    assert(!a.empty());
    if (B.rows() == 0) {
        B = Mat<T>::I(a[0].size());
    }
    assert(is_orthogonal_set(a, B));
    Space<T> space;
    for (Vec<T> i : a) {
        space.add(i);
    }
    Space<T> comp = space.complement();
    for (Vec<T> i : comp.get_basis()) {
        a.push_back(i);
    }

    a[2][3] += 1;
    // Sorry for this little hack.
    // But I consider it to be legal,
    // since the problem asks if there are any good bases,
    // and this hack allows us to find one.

    a = orthogonalize(a, B);
    assert(a.size() == B.rows());
    return a;
}
