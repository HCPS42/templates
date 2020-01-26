#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int, int>
#define fi first
#define se second
#define prev previous

// k balls are given.
// How many vertices lie in at least (k - 1) of them?

const int N = 2e5 + 5;
const int inf = 1e9;

vector<int> g[N];
bool used[N];
int sz[N], max_sz[N];
vector<int> vis;
map<int, vector<int>> sub[N];
vector<int> Sub[N];
pii prev[N];
map<int, int> dist_to_center[N];
int n;

void calc_sizes(int v, int par) {
	vis.pb(v);
	sz[v] = 1;
	max_sz[v] = 0;
	for (int u : g[v]) {
		if (u == par || used[u]) continue;
		calc_sizes(u, v);
		sz[v] += sz[u];
		max_sz[v] = max(max_sz[v], sz[u]);
	}
}

int get_center(int v) {
	vis.clear();
	calc_sizes(v, 0);
	int min_size = inf;
	int center = -1;
	for (int u : vis) {
		int size = max(max_sz[u], (int)vis.size() - sz[u]);
		if (min_size > size) {
			min_size = size;
			center = u;
		}
	}
	used[center] = 1;
	return center;
}

void calc_dist_to_center(int v, int par, int cur_dist, int center, int child) {
	if (v <= n) {
		sub[center][child].pb(cur_dist);
		Sub[center].pb(cur_dist);
	}
	dist_to_center[v][center] = cur_dist;
	for (int u : g[v]) {
		if (u == par || used[u]) continue;
		calc_dist_to_center(u, v, cur_dist + 1, center, child);
	}
}

void centroid_decomposition() {
	queue<int> q;
	int first_center = get_center(1);
	q.push(first_center);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int u : g[v]) {
			if (!used[u]) {
				calc_dist_to_center(u, v, 1, v, u);
				sort(sub[v][u].begin(), sub[v][u].end());
			}
		}
		sort(Sub[v].begin(), Sub[v].end());
		for (int u : g[v]) {
			if (!used[u]) {
				int new_center = get_center(u);
				prev[new_center] = {v, u};
				q.push(new_center);
			}
		}
	}
}

int count(int start, int max_dist) {
	int child = 0;
	int v = start;
	int res = 0;
	while (v) {
        int cur_max_dist = max_dist - dist_to_center[start][v];
        if (cur_max_dist >= 0 && v <= n) res++;
		res += upper_bound(Sub[v].begin(), Sub[v].end(), cur_max_dist) - Sub[v].begin();
		res -= upper_bound(sub[v][child].begin(), sub[v][child].end(), cur_max_dist) - sub[v][child].begin();
		child = prev[v].se;
		v = prev[v].fi;
	}
	return res;
}

int count_good(int v, int r) {
	int res = count(v, r);
	return res;
}

const int L = ceil(log2(N)) + 1;

int in[N], out[N];
int up[N][L];
int lvl[N];
int timer = 1;

void dfs_lca(int v = 1, int p = 1) {
	in[v] = timer++;
	up[v][0] = p;
	for (int i=1; i<L; i++) {
		up[v][i] = up[up[v][i-1]][i-1];
	}
	for (int u : g[v]) {
		if (u != p) {
			lvl[u] = lvl[v] + 1;
			dfs_lca(u, v);
		}
	}
	out[v] = timer - 1;
}

bool is_anc(int u, int v) {
	return in[u] <= in[v] && in[v] <= out[u];
}

int lca(int u, int v) {
	if (u > v) swap(u, v);
	int res;
	if (is_anc(u, v)) res = u;
	else if (is_anc(v, u)) res = v;
	else {
		int cur = u;
		for (int i=L-1; i>=0; i--) {
			if (!is_anc(up[cur][i], v)) cur = up[cur][i];
		}
		res = up[cur][0];
	}
	return res;
}

pii inter(pii ball1, pii ball2) {
	int v = ball1.fi, r1 = ball1.se;
	int u = ball2.fi, r2 = ball2.se;
	if (!v || !u) return {0, 0};
	int l = lca(v, u);
	int d = lvl[v] + lvl[u] - 2 * lvl[l];
	pii ans;
	if (d > r1 + r2) ans = {0, 0};
	else if (r1 >= r2 + d) ans = {u, r2};
	else if (r2 >= r1 + d) ans = {v, r1};
	else {
		int x = (d + r1 - r2) / 2;
		int r = (r1 + r2 - d) / 2;
		if (lvl[v] - lvl[l] >= x) {
			for (int i=0; i<L; i++) {
				if ((1 << i) > x) break;
				if (x & (1 << i)) {
					v = up[v][i];
				}
			}
			x = v;
		}
		else {
			x -= lvl[v] - lvl[l];
			x = lvl[u] - lvl[l] - x;
			for (int i=0; i<L; i++) {
				if ((1 << i) > x) break;
				if (x & (1 << i)) {
					u = up[u][i];
				}
			}
			x = u;
		}
		ans = {x, r};
	}
	return ans;
}

pii pref[N*2], suf[N*2];

void init() {
	cin >> n;
	int last = n;
	for (int i=1; i<n; i++) {
		int u, v;
		cin >> u >> v;
		last++;
		g[u].pb(last);
		g[v].pb(last);
		g[last].pb(u);
		g[last].pb(v);
	}
	centroid_decomposition();
	dfs_lca();
}

ll solve() {
	int k;
	cin >> k;
	for (int i=1; i<=k; i++) {
		int v, r;
		cin >> v >> r;
		pref[i] = {v, 2 * r};
		suf[i] = {v, 2 * r};
	}
	for (int i=2; i<=k; i++) {
		pref[i] = inter(pref[i], pref[i-1]);
	}
	for (int i=k-1; i>=1; i--) {
		suf[i] = inter(suf[i], suf[i+1]);
	}
	ll ans = 0;
	pref[0] = suf[k+1] = {1, 2*n};
	for (int i=1; i<=k; i++) {
		pii cur = inter(pref[i-1], suf[i+1]);
		if (cur.fi) ans += count_good(cur.fi, cur.se);
	}
	pii all = pref[k];
	if (all.fi) ans -= (k-1) * 1ll * count_good(all.fi, all.se);
	return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
	init();
	int T;
	cin >> T;
	while (T--) {
		cout << solve() << endl;
	}
    return 0;
}
