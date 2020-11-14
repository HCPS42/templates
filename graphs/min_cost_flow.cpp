#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second

const int N = 205;
const ll inf = 1e18;
const int INF = 1e9;

int prev_edge[N];
int prev_vert[N];
ll prio[N];
int cur_flow[N];
int dist[N];

struct Edge {
	int to;
	int flow, cap, cost;
	int rev;
	int id;
};

vector<Edge> g[N];

void add_edge(int s, int e, int cap, int cost, int id) {
	Edge f = {e, 0, cap, cost, g[e].size(), id};
	Edge b = {s, 0, 0, -cost, g[s].size(), id};
	g[s].pb(f);
	g[e].pb(b);
}

pair<int, int> min_cost_flow(int src, int sink, int max_flow) {
	int flow = 0;
	int cost = 0;
	while (flow < max_flow) {
		priority_queue<ll> pq;
		pq.push(src);
		for (int i=0; i<N; i++) {
			prio[i] = inf;
		}
		prio[src] = 0;
		cur_flow[src] = INF;
		while (!pq.empty()) {
			ll ver = pq.top();
			pq.pop();
			if ((ver >> 32) != prio[int(ver)]) continue;
			int v = ver;
			for (int i=0; i<g[v].size(); i++) {
				Edge& e = g[v][i];
				int u = e.to;
				if (e.cap <= e.flow) continue;
				if (prio[u] > prio[v] + e.cost + dist[v] - dist[u]) {
					prio[u] = prio[v] + e.cost + dist[v] - dist[u];
					pq.push((prio[u] << 32) + u);
					prev_vert[u] = v;
					prev_edge[u] = i;
					cur_flow[u] = min(cur_flow[v], e.cap - e.flow);
				}
			}
		}
		if (prio[sink] == inf) break;
		for (int i=0; i<N; i++) {
			dist[i] += prio[i];
		}
		int pushed = min(cur_flow[sink], max_flow - flow);
		flow += pushed;
		int v = sink;
		while (v != src) {
			Edge& e = g[prev_vert[v]][prev_edge[v]];
			e.flow += pushed;
			g[v][e.rev].flow -= pushed;
			cost += pushed * e.cost;
			v = prev_vert[v];
		}
	}
	return {flow, cost};
}

vector<vector<int>> ans;
vector<int> path;
bool used[2005];
int src, sink;

bool good(Edge& e) {
	return e.flow > 0 && !used[e.id];
}

void dfs(int v = 1) {
	if (v == sink) {
		ans.pb(path);
		return;
	}
	for (Edge& e : g[v]) {
		if (!good(e)) continue;
		used[e.id] = 1;
		path.pb(e.id);
		dfs(e.to);
		path.ppp();
		if (v != src) return;
	}
}

void Solve() {
	int n, m, k;
	cin >> n >> m >> k;
	src = 1;
	sink = n;
	for (int i=1; i<=m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		add_edge(u, v, 1, w, i);
		add_edge(v, u, 1, w, i);
	}
	pair<int, int> data = min_cost_flow(src, sink, k);
	if (data.fi < k) {
		cout << "-1\n";
		return;
	}
	dfs();
	cout << fixed << setprecision(12);
	cout << double(data.se) / k << "\n";
	//assert(ans.size() == k);
	for (int i=0; i<k; i++) {
		cout << ans[i].size() << " ";
		for (int j : ans[i]) {
			cout << j << " ";
		}
		cout << "\n";
	}
}

// https://official.contest.yandex.com/mw2020prefinals/contest/18101/problems/H4b/

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    freopen("brides.in", "r", stdin);
    freopen("brides.out", "w", stdout);
#endif
	Solve();
    return 0;
}
