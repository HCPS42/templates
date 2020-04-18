#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int, int>
#define fi first
#define se second

const ll inf = 1e18;

// min cost matching
pair<ll, vector<int>> assignment(vector<vector<ll>> a) {
	int n = a.size();
	int m = a[0].size();
	vector<ll> u(n + 1, 0);
	vector<ll> v(m + 1, 0);
	vector<int> p(m + 1, 0);
	vector<int> way(m + 1, 0);
	for (int i=1; i<=n; i++) {
		p[0] = i;
		int j0 = 0;
		vector<ll> minv(m + 1, inf);
		vector<bool> used(m + 1, 0);
		while (1) {
			used[j0] = 1;
			int i0 = p[j0];
			ll delta = inf;
			int j1;
			for (int j=1; j<=m; j++) {
				if (used[j]) continue;
				ll cur = a[i0 - 1][j - 1] - u[i0] - v[j];
				if (cur < minv[j]) {
					minv[j] = cur;
					way[j] = j0;
				}
				if (minv[j] < delta) {
					delta = minv[j];
					j1 = j;
				}
			}
			for (int j=0; j<=m; j++) {
				if (used[j]) {
					u[p[j]] += delta;
					v[j] -= delta;
				}
				else {
					minv[j] -= delta;
				}
			}
			j0 = j1;
			if (!p[j0]) break;
		}
		while (1) {
			int j1 = way[j0];
			p[j0] = p[j1];
			j0 = j1;
			if (!j0) break;
		}
	}
	ll cost = -v[0];
	vector<int> ans(n + 1);
	for (int j=1; j<=m; j++) {
		ans[p[j]] = j;
	}
	return {cost, ans};
}

void Solve() {
	
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	Solve();
	return 0;
}
