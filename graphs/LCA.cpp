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
int in[N], out[N];
int up[N][L];
int timer = 1;

void dfs_lca(int v = 1, int p = 1) {
	in[v] = timer++;
	up[v][0] = p;
	for (int i=1; i<L; i++) {
		up[v][i] = up[up[v][i-1]][i-1];
	}
	for (int u : g[v]) {
		if (u != p) dfs_lca(u, v);
	}
	out[v] = timer - 1;
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

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
	// read
	dfs_lca();
	
	return 0;
}
