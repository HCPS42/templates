#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define fi first
#define se second
#define pii pair<int,int>

struct num {
	const ll p = 1e9 + 7;
	ll x = 0;
	num() {}
	num(ll x_) {
        x_ %= p;
        if (x_ < 0) x_ += p;
        x = x_;
	}
	num operator+(num y) { return num(x + y.x); }
	num operator+(ll y) { return num(x + y); }
	num operator+=(num y) { return x = (x + y.x) % p; }
	num operator+=(ll y) { return x = (x + y) % p; }
	num operator-(num y) { return num(x - y.x + p); }
	num operator-(ll y) { return num(x - y + p); }
	num operator-=(num y) { return x = (x - y.x + p) % p; }
	num operator-=(ll y) { return x = (x - y + p) % p; }
	num operator*(num y) { return num(x * y.x); }
	num operator*(ll y) { return num(x * y); }
	num operator*=(num y) { return x = x * y.x % p; }
	num operator*=(ll y) { return x = x * y % p; }
	num operator/(num y) { return *this * y.inv(); }
	num operator/(ll y) { return *this * num(y).inv(); }
	num operator/=(num y) { return *this *= y.inv(); }
	num operator/=(ll y) { return *this *= num(y).inv(); }
	num operator=(num y) { return x = y.x; }
	num operator=(ll y) { return x = y; }
	num pow(ll y) {
		num res(1);
		num cur(x);
		while (y) {
			if (y & 1) res *= cur;
			y >>= 1;
			cur *= cur;
		}
		return res;
	}
    num inv() {
		return pow(p-2);
	}
	operator ll() {
		return x;
	}
};

struct mat {
	static const int K = 3;
	num x[K][K];
    mat() {}
	void zero() {
		for (int i=0; i<K; i++) {
			for (int j=0; j<K; j++) {
				x[i][j] = 0;
			}
		}
	}
	void id() {
		zero();
		for (int i=0; i<K; i++) {
			x[i][i] = 1;
		}
	}
	mat operator+(mat y) {
		mat res;
		for (int i=0; i<K; i++) {
			for (int j=0; j<K; j++) {
				res.x[i][j] = x[i][j] + y.x[i][j];
			}
		}
		return res;
	}
	mat operator+(num y) {
		mat res;
		for (int i=0; i<K; i++) {
			for (int j=0; j<K; j++) {
				res.x[i][j] = x[i][j] + y;
			}
		}
		return res;
	}
	mat operator+(ll y) {
		return *this + num(y);
	}
	mat operator+=(mat y) {
		for (int i=0; i<K; i++) {
			for (int j=0; j<K; j++) {
				x[i][j] += y.x[i][j];
			}
		}
		return *this;
	}
	mat operator+=(num y) {
		for (int i=0; i<K; i++) {
			for (int j=0; j<K; j++) {
				x[i][j] += y;
			}
		}
		return *this;
	}
	mat operator+=(ll y) {
		return *this += num(y);
	}
	mat operator-(mat y) {
		mat res;
		for (int i=0; i<K; i++) {
			for (int j=0; j<K; j++) {
				res.x[i][j] = x[i][j] - y.x[i][j];
			}
		}
		return res;
	}
	mat operator-(num y) {
		mat res;
		for (int i=0; i<K; i++) {
			for (int j=0; j<K; j++) {
				res.x[i][j] = x[i][j] - y;
			}
		}
		return res;
	}
	mat operator-(ll y) {
		return *this - num(y);
	}
	mat operator-=(mat y) {
		for (int i=0; i<K; i++) {
			for (int j=0; j<K; j++) {
				x[i][j] -= y.x[i][j];
			}
		}
		return *this;
	}
	mat operator-=(num y) {
		for (int i=0; i<K; i++) {
			for (int j=0; j<K; j++) {
				x[i][j] -= y;
			}
		}
		return *this;
	}
	mat operator-=(ll y) {
		return *this -= num(y);
	}
	mat operator*(mat y) {
		mat res;
		for (int i=0; i<K; i++) {
			for (int j=0; j<K; j++) {
				for (int k=0; k<K; k++) {
					res.x[i][j] += x[i][k] * y.x[k][j];
				}
			}
		}
		return res;
	}
    mat operator*(num y) {
		mat res;
		for (int i=0; i<K; i++) {
			for (int j=0; j<K; j++) {
				res.x[i][j] = x[i][j] * y;
			}
		}
		return res;
    }
	mat operator*(ll y) {
		return *this * num(y);
	}
	mat operator*=(mat y) {
		mat res;
		for (int i=0; i<K; i++) {
			for (int j=0; j<K; j++) {
				for (int k=0; k<K; k++) {
					res.x[i][j] += x[i][k] * y.x[k][j];
				}
			}
		}
		*this = res;
		return *this;
	}
	mat operator*=(num y) {
		for (int i=0; i<K; i++) {
			for (int j=0; j<K; j++) {
				x[i][j] *= y;
			}
		}
		return *this;
	}
	mat operator*=(ll y) {
		return *this *= num(y);
	}
	void print() {
		for (int i=0; i<K; i++) {
			for (int j=0; j<K; j++) {
				cout << x[i][j] << " ";
			}
			cout << "\n";
		}
		cout << "\n";
	}
};

ll phi(ll x) {
    ll res = x;
    for (int i=2; i*i<=x; i++) {
        if (x % i == 0) {
            while (x % i == 0) x /= i;
            res -= res / i;
        }
    }
    if (x > 1) res -= res / x;
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    
    return 0;
}
