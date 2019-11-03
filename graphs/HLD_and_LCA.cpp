#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define fi first
#define se second
#define pii pair<int,int>

const int N = 1e5 + 5;
const int L = ceil(log2(N)) + 2;

vector<int> g[N];
int sz[N], in[N], out[N], nxt[N];
int timer = 1;
int parent[N];
int up[N][L];
// nxt[v] --- the highest vertex in the heavy path corresponding to v
// [in[v]; out[v]] --- subtree of v
// [in[nxt[v]]; in[v]] --- path from nxt[v] to v

void dfs_par(int v = 1, int p = 1) {
	parent[v] = p;
	for (int u : g[v]) {
		if (u == p) continue;
		dfs_par(u, v);
	}
}

void dfs_sz(int v = 1) {
	sz[v] = 1;
	for (int &u : g[v]) {
		dfs_sz(u);
		sz[v] += sz[u];
		if (sz[u] > sz[g[v][0]]) {
			swap(u, g[v][0]);
		}
	}
}

void dfs_hld(int v = 1) {
	in[v] = timer++;
	for (int u : g[v]) {
		nxt[u] = (u == g[v][0] ? nxt[v] : u); // paths don't include light edges
		dfs_hld(u);
	}
	out[v] = timer - 1;
}

void dfs_lca(int v = 1) {
	up[v][0] = parent[v];
	for (int i=1; i<L; i++) {
		up[v][i] = up[up[v][i-1]][i-1];
	}
	for (int u : g[v]) dfs_lca(u);
}

bool is_anc(int u, int v) {
	return in[u] <= in[v] && in[v] <= out[u];
}

int lca(int u, int v) {
	if (is_anc(u, v)) return u;
	else if (is_anc(v, u)) return v;
	for (int i=L-1; i>=0; i--) {
		if (!is_anc(up[u][i], v)) u = up[u][i];
	}
	return up[u][0];
}

void init() {
	dfs_par();
	for (int i=0; i<N; i++) {
		vector<int> cur;
		for (int u : g[i]) {
			if (u != parent[i]) cur.pb(u);
		}
		g[i] = cur;
	}
	dfs_sz();
	dfs_hld();
	dfs_lca();
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
	// read
	init();
	return 0;
}
