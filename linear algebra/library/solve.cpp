#include <bits/stdc++.h>
#include "11_cholesky.h"

int main() {
    Mat<Real> A(
{{3, 1, 9, 7, 0},
{1, 2, 0, 0, 0},
{9, 0, 5, 0, 0}, 
{7, 0, 0, 1, 3}, 
{0, 0, 0, 3, 4}}
);
    cout << A << endl;
    cout << cholesky_decomposition(A) << endl;
}
