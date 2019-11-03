#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int, int>
#define fi first
#define se second
#define prev previous

const int N = 1e5 + 5;
const int inf = 1e9;

vector<pii> g[N];
bool used[N];
int sz[N], max_sz[N];
vector<int> vis;
map<int, vector<ll>> sub[N];
vector<ll> Sub[N];
pii prev[N];
map<pii, ll> dist_to_center;

void calc_sizes(int v, int par) {
	vis.pb(v);
	sz[v] = 1;
	max_sz[v] = 0;
	for (pii edge : g[v]) {
		int u = edge.fi;
		int w = edge.se;
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

void calc_dist_to_center(int v, int par, ll cur_dist, int center, int child) {
	sub[center][child].pb(cur_dist);
	Sub[center].pb(cur_dist);
	dist_to_center[{v, center}] = cur_dist;
	for (pii edge : g[v]) {
		int u = edge.fi;
		int w = edge.se;
		if (u == par || used[u]) continue;
		calc_dist_to_center(u, v, cur_dist + w, center, child);
	}
}

void centroid_decomposition() {
	queue<int> q;
	int first_center = get_center(1);
	q.push(first_center);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (pii edge : g[v]) {
			int u = edge.fi;
			int w = edge.se;
			if (!used[u]) {
				calc_dist_to_center(u, v, w, v, u);
				sort(sub[v][u].begin(), sub[v][u].end());
			}
		}
		sort(Sub[v].begin(), Sub[v].end());
		for (pii edge : g[v]) {
			int u = edge.fi;
			int w = edge.se;
			if (!used[u]) {
				int new_center = get_center(u);
				prev[new_center] = {v, u};
				q.push(new_center);
			}
		}
	}
}

int solve(int start, ll max_dist) {
	int child = 0;
	int v = start;
	int res = 0;
	while (v) {
        ll cur_max_dist = max_dist - dist_to_center[{start, v}];
        if (cur_max_dist >= 0) res++;
		res += upper_bound(Sub[v].begin(), Sub[v].end(), cur_max_dist) - Sub[v].begin();
		res -= upper_bound(sub[v][child].begin(), sub[v][child].end(), cur_max_dist) - sub[v][child].begin();
		child = prev[v].se;
		v = prev[v].fi;
	}
	return res;
}

// Problem: https://codeforces.com/group/qcIqFPYhVr/contest/203881/problem/X
// Count the number of vertices at the distance of at most max_dist from given vertex v.

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
	int n, T;
	cin >> n >> T;
	for (int i=1; i<=n-1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].pb({v, w});
		g[v].pb({u, w});
	}
	centroid_decomposition();
	while (T--) {
		int v;
		ll max_dist;
		cin >> v >> max_dist;
		int ans = solve(v, max_dist);
		cout << ans << "\n";
	}
    return 0;
}
