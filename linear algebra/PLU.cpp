#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second

typedef vector<double> row;
typedef vector<row> mat;
mat I;

const double eps = 1e-6;

vector<mat> PLU(mat U) {
	/*
	Gaussian elimination with partial pivoting
	PLU factorization
	A \in M_n[\R]
	PA = LU
	P --- permutation matrix
	L --- lower-triangular matrix
	U --- upper-triangular matrix
	time complexity = O(n^3)
	*/
	mat L = I, P = I;
	int n = U.size();
	for (int k=0; k<n-1; k++) {
		int i = k;
		for (int j=k; j<n; j++) {
			if (abs(U[j][k]) > abs(U[i][k])) i = j;
		}
		if (abs(U[i][k]) <= eps) continue;
		swap(U[i], U[k]);
		for (int t=0; t<k-1; t++) {
			swap(L[k][t], L[i][t]);
		}
		swap(P[i], P[k]);
		for (int j=k+1; j<n; j++) {
			L[j][k] = U[j][k] / U[k][k];
			for (int t=k; t<n; t++) {
				U[j][t] -= L[j][k] * U[k][t];
			}
		}
	}
	return {P, L, U};
}

mat mult(mat A, mat B) {
	int m = A.size();
	int n = A[0].size();
	assert(B.size() == n);
	int k = B[0].size();
	mat res(m, row(k));
	for (int i=0; i<m; i++) {
		for (int j=0; j<k; j++) {
			for (int t=0; t<n; t++) {
				res[i][j] += A[i][t] * B[t][j];
			}
		}
	}
	return res;
}

mat solve(mat A, mat b) {
	/*
	solve Ax = b by using PLU
	time complexity = O(n^3)
	*/
	vector<mat> plu = PLU(A);
	mat P = plu[0], L = plu[1], U = plu[2];
	int n = A.size();
	mat x(n, row(1, 0));
	mat y = x;
	b = mult(P, b);
	for (int i=0; i<n; i++) {
		if (abs(L[i][i]) <= eps) {
			if (abs(b[i][0]) <= eps) {
				y[i][0] = 0; // free variable
			}
			else {
				cerr << "No solution\n";
				assert(0);
			}
		}
		else y[i][0] = b[i][0] / L[i][i];
		for (int j=i+1; j<n; j++) {
			b[j][0] -= y[i][0] * L[j][i];
		}
	}
	for (int i=n-1; i>=0; i--) {
		if (abs(U[i][i]) <= eps) {
			if (abs(y[i][0]) <= eps) {
				x[i][0] = 0; // free variable
			}
			else {
				cerr << "No solution\n";
				assert(0);
			}
		}
		else x[i][0] = y[i][0] / U[i][i];
		for (int j=i-1; j>=0; j--) {
			y[j][0] -= x[i][0] * U[j][i];
		}
	}
	return x;
}


int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	int n;
	cin >> n;
	if (n == 0) return 0;
	mat A(n, row(n));
	mat b(n, row(1));
	I = mat(n, row(n, 0));
	for (int i=0; i<n; i++) I[i][i] = 1;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) cin >> A[i][j];
		cin >> b[i][0];
	}
	mat x = solve(A, b);
	cout << fixed << setprecision(12);
	for (int i=0; i<n; i++) {
		cout << x[i][0] << " ";
	}
	cout << "\n";
	return 0;
}
