#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second

class Mat {
public:
	Mat(int n_, int m_) : n(n_), m(m_) {
		a.resize(n, vector<int>(m, 0));
	}
	explicit Mat(int n_) : Mat(n_, n_) {
	}
	explicit Mat(vector<vector<int>>& b) {
		n = b.size();
		m = b[0].size();
		a = b;
	}
	int rows() {
		return n;
	}
	int cols() {
		return m;
	}
	int& operator()(int i, int j) {
		return a[i][j];
	}
	int operator()(int i, int j) const {
		return a[i][j];
	}
	Mat& operator+=(Mat& b) {
		for (int i=0; i<n; i++) {
			for (int j=0; j<m; j++) {
				a[i][j] += b(i, j);
			}
		}
		return *this;
	}
	Mat operator+(Mat& b) {
		Mat sum(a);
		return sum += b;
	}
	Mat& operator-=(Mat& b) {
		for (int i=0; i<n; i++) {
			for (int j=0; j<m; j++) {
				a[i][j] -= b(i, j);
			}
		}
		return *this;
	}
	Mat operator-(Mat& b) {
		Mat sum(a);
		return sum -= b;
	}
	Mat operator*(Mat& b) {
		Mat c(n, b.cols());
		for (int i=0; i<n; i++) {
			for (int j=0; j<b.cols(); j++) {
				for (int k=0; k<m; k++) {
					c(i, j) += a[i][k] * b(k, j);
				}
			}
		}
		return c;
	}
	Mat operator*=(Mat& b) {
		(*this) = (*this) * b;
		return *this;
	}
	Mat T() {
		Mat tr(m, n);
		for (int i=0; i<n; i++) {
			for (int j=0; j<m; j++) {
				tr(j, i) = a[i][j];
			}
		}
		return tr;
	}
	void I(int n_) {
		n = m = n_;
		a.resize(n_, vector<int>(n_, 0));
		for (int i=0; i<n; i++) a[i][i] = 1;
	}

private:
    vector<vector<int>> a;
    int n, m;
};

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif

	return 0;
}
