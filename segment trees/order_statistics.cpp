#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second

// https://www.spoj.com/problems/MKTHNUM/

const int N = 1e5 + 5;
const int inf = 1e9;
const int logn = 20;
const int S = N * logn;

int t[S];
int lef[S], rig[S];
int roots[N];
int sz = 1, rt = 1;

int copy(int v) {
	lef[sz] = lef[v];
	rig[sz] = rig[v];
	t[sz] = t[v];
	return sz++;
}

int make_root(int r = rt-1) {
	roots[rt] = copy(roots[r]);
	return rt++;
}

void build(int v=0, int l=1, int r = N-1) {
    t[v] = 0;
    if (l < r) {
        int m = (l + r) / 2;
        lef[v] = sz++;
        rig[v] = sz++;
        build(lef[v], l, m);
        build(rig[v], m+1, r);
    }
}

void upd(int id, int x, int v, int l = 1, int r = N-1) {
	if (l == r) t[v] += x;
	else {
		int m = (l + r) / 2;
		if (id <= m) upd(id, x, lef[v] = copy(lef[v]), l, m);
		else upd(id, x, rig[v] = copy(rig[v]), m+1, r);
		t[v] = t[lef[v]] + t[rig[v]];
	}
}

int get(int u, int v, int k, int l=1, int r=N-1) {
	if (l == r) return l;
	int m = (l + r) / 2;
	int cnt = t[lef[v]] - t[lef[u]];
	if (cnt >= k) return get(lef[u], lef[v], k, l, m);
	return get(rig[u], rig[v], k - cnt, m+1, r);
}

int a[N], invMap[N];
map<int, int> Map;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	int n, T;
	cin >> n >> T;
	for (int i=1; i<=n; i++) {
		cin >> a[i];
		Map[a[i]] = 0;
	}
	int index = 1;
	for (auto it=Map.begin(); it!=Map.end(); it++) {
		Map[it->fi] = index;
		invMap[index] = it->fi;
		index++;
	}
	//build();
	for (int i=1; i<=n; i++) {
		upd(Map[a[i]], 1, roots[make_root()]);
	}
	while (T--) {
		int l, r, k;
		cin >> l >> r >> k;
		int cur = get(roots[l-1], roots[r], k);
		int ans = invMap[cur];
		cout << ans << "\n";
	}
	return 0;
}
