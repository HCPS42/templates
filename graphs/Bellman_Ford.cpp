#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define fi first
#define se second
#define pii pair<int, int>

const int N = 2005;
const ll inf = 7e18;

struct Edge {
	int u, v;
	ll w;
};

vector<int> g[N];
vector<Edge> edges;
ll dist[N];
bool used[N];
vector<int> reachable;
map<pii, ll> wei;

bool relax(Edge& e) {
	int u = e.u, v = e.v;
	ll w = e.w;
	if (dist[u] < inf && dist[v] > -inf && dist[v] > dist[u] + w) {
		dist[v] = dist[u] + w;
		return 1;
	}
	return 0;
}

void bellman_ford(int n) {
	for (int i=1; i<=n-1; i++) {
		for (Edge& e : edges) {
			relax(e);
		}
	}
}

void reachable_from_negative_cycles() {
	for (Edge& e : edges) {
		if (relax(e)) reachable.pb(e.v);
	}
}

void dfs(int v) {
	used[v] = 1;
	dist[v] = -inf;
	for (int u : g[v]) {
		if (!used[u]) dfs(u);
	}
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
	int n, m, start;
	cin >> n >> m >> start;
	for (int i=1; i<=m; i++) {
		int u, v;
		ll w;
		cin >> u >> v >> w;
		if (wei.count({u, v})) {
			wei[{u, v}] = min(wei[{u, v}], w);
		}
		else {
			wei[{u, v}] = w;
			edges.pb({u, v, w});
			g[u].pb(v);
		}
	}
	for (Edge& e : edges) {
		e.w = wei[{e.u, e.v}];
	}
	for (int i=1; i<=n; i++) dist[i] = inf;
	dist[start] = 0;
	bellman_ford(n);
	reachable_from_negative_cycles();
	for (int v : reachable) {
		if (!used[v]) dfs(v);
	}
	for (int i=1; i<=n; i++) {
		if (dist[i] == inf) cout << "*\n";
		else if (dist[i] == -inf) cout << "-\n";
		else cout << dist[i] << "\n";
	}
	return 0;
}
