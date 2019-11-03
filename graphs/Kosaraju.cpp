#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define fi first
#define se second
#define pii pair<int, int>

const int N = 1e5 + 5;

vector<int> g[2][N];
bool used[N];
vector<int> post;
vector<vector<int>> comps;

void dfs_inv(int v) {
	used[v] = 1;
	for (int u : g[1][v]) {
		if (!used[u]) dfs_inv(u);
	}
	post.pb(v);
}

void dfs(int v, vector<int> &comp) {
	used[v] = 1;
	comp.pb(v);
	for (int u : g[0][v]) {
		if (!used[u]) dfs(u, comp);
	}
}

void kosaraju(int n) {
	for (int i=1; i<=n; i++) used[i] = 0;
	for (int i=1; i<=n; i++) {
		if (!used[i]) dfs_inv(i);
	}
	reverse(post.begin(), post.end());
	for (int i=1; i<=n; i++) used[i] = 0;
	for (int v : post) {
		if (!used[v]) {
			vector<int> comp;
			dfs(v, comp);
			comps.pb(comp);
		}
	}
	// comps = reversed topsort
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    // read
	kosaraju(n);
    return 0;
}
