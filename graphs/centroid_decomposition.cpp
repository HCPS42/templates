#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int, int>
#define fi first
#define se second

const int N = 1e6 + 5;
const int inf = 1e9;

vector<int> g[N];
bool used[N];
int sz[N], max_sz[N];
vector<int> vis;

void dfs(int v, int p = 0) {
	vis.pb(v);
	sz[v] = 1;
	max_sz[v] = 0;
	for (int u : g[v]) {
		if (u == p || used[u]) continue;
		dfs(u, v);
		sz[v] += sz[u];
		max_sz[v] = max(max_sz[v], sz[u]);
	}
}

int get_center(int v) {
	vis.clear();
	dfs(v);
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

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
    
	return 0;
}
