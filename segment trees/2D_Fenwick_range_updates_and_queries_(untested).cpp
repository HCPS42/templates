#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define fi first
#define se second
#define pii pair<int, int>

// UNTESTED

const int N = 1005;

ll p[4][N][N];

void add(int tp, int x, int y, ll del) { // (i, j) += del in array #tp
	for (int i=x; i<N; i += i & -i) {
		for (int j=y; j<N; j += j & -j) {
			p[tp][i][j] += del;
		}
	}
}

ll sum(int tp, int x, int y) { // sum of [1, x] \times [1, y] in array #tp
	ll res = 0;
	for (int i=x; i>=1; i -= i & -i) {
		for (int j=y; j>=1; j -= j & -j) {
			res += p[tp][i][j];
		}
	}
	return res;
}

void upd(int x, int y, ll del) { // [x, n] \times [y, m] += del
	add(0, x, y, del);
	add(1, x, y, del * (1 - y));
	add(2, x, y, del * (1 - x));
	add(3, x, y, del * (1 - x) * (1 - y));
}

void upd(int x1, int y1, int x2, int y2, ll del) { // [x1, x2] \times [y1, y2] += del
	upd(x1, y1, del);
	upd(x1, y2+1, -del);
	upd(x2+1, y1, -del);
	upd(x2+1, y2+1, del);
}

ll get(int x, int y) { // sum of [1, x] \times [1, y]
	return sum(0, x, y) * x * y + sum(1, x, y) * x + sum(2, x, y) * y + sum(3, x, y);
}

ll get(int x1, int y1, int x2, int y2) { // sum of [x1, x2] \times [y1, y2]
	return get(x2, y2) - get(x2, y1-1) - get(x1-1, y2) + get(x1-1, y1-1);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	int n, m, T;
	cin >> n >> m >> T;
	while (T--) {
		int tp;
		cin >> tp;
		if (tp == 1) {
			int x1, y1, x2, y2;
			ll del;
			cin >> x1 >> y1 >> x2 >> y2 >> del;
			upd(x1, y1, x2, y2, del);
		}
		else {
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			ll res = get(x1, y1, x2, y2);
			cout << res << "\n";
		}
	}
	return 0;
}
