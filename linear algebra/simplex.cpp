#include <bits/stdc++.h>
using namespace std;

typedef vector<double> Vec;
const double eps = 1e-8;

// Ax <= b, maximize c^Tx
// x >= 0

Vec simplex(vector<Vec> A, Vec b, Vec c) {
    int n = A.size();
    int m = A[0].size() + 1;
    int r = n;
    int s = m - 1;
    vector<Vec> D(n + 2, Vec(m + 1));
    vector<int> ix(n + m);
    for (int i = 0; i < n + m; i++) ix[i] = i;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) D[i][j] = -A[i][j];
        D[i][m - 1] = 1;
        D[i][m] = b[i];
        if (D[r][m] > D[i][m]) r = i;
    }
    for (int j = 0; j < m - 1; j++) D[n][j] = c[j];
    D[n + 1][m - 1] = -1;
    double d;
    while (1) {
        if (r < n) {
            swap(ix[s], ix[r+m]);
            D[r][s] = 1.0 / D[r][s];
            for (int j = 0; j <= m; j++) {
                if (j != s) {
                    D[r][j] *= -D[r][s];
                }
            }
            for (int i = 0; i <= n + 1; i++) {
                if (i == r) continue;
                for (int j = 0; j <= m; j++) {
                    if (j != s) {
                        D[i][j] += D[r][j] * D[i][s];
                    }
                }
                D[i][s] *= D[r][s];
            }
        }
        r = s = -1;
        for (int j = 0; j < m; j++) {
            if (s < 0 || ix[s] > ix[j]) {
                if (D[n + 1][j] > eps || D[n + 1][j] > -eps && D[n][j] > eps) {
                    s = j;
                }
            }
        }
        if (s < 0) break;
        for (int i = 0; i < n; i++) {
            if (D[i][s] < -eps) {
                if (r < 0 || (d = D[r][m] / D[r][s] - D[i][m] / D[i][s]) < -eps
                    || d < eps && ix[r + m] > ix[i + m]) {
                    r = i;
                }
            }
        }
        if (r < 0) {
            return {}; // unbounded
        }
    }
    if (D[n + 1][m] < -eps) {
        return {}; // infeasible
    }
    Vec x(m - 1);
    for (int i = m; i < n + m; i++) {
        if (ix[i] < m - 1) {
            x[ix[i]] = D[i - m][m];
        }
    }
    return x; // ans: D[n][m]
}

int main() {
    return 0;
}
