#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/contest/1510/problem/B

// supports negative costs: yes
// supports negative cycles: I don't know

typedef long long ll;

const int N = 2005;
const ll inf = 4e18;

pair<int, int> par[N];
ll phi[N];
ll flo[N];
ll dis[N];

struct Edge {
	int to;
	ll flow;
	ll cap;
	ll cost;
	int rev;
};

vector<Edge> g[N];

void init_mcmf() {
    for (int i = 0; i < N; i++) {
		par[i] = {0, 0};
		phi[i] = 0;
		flo[i] = 0;
		dis[i] = 0;
		g[i].clear();
	}
}

void add_edge(int s, int e, ll cap, ll cost) {
	Edge f = {e, 0, cap, cost, (int) g[e].size()};
	Edge b = {s, 0, 0, -cost, (int) g[s].size()};
	g[s].push_back(f);
	g[e].push_back(b);
}

pair<ll, ll> min_cost_max_flow(int src, int sink, ll bound = inf) {
	ll flow = 0;
	ll cost = 0;
	while (1) {
		priority_queue<pair<ll, int>> q;
		for (int i = 0; i < N; i++) {
			phi[i] = inf;
		}
		phi[src] = 0;
		q.push({phi[src], src});
		flo[src] = inf;
		while (!q.empty()) {
			pair<ll, int> ver = q.top();
			q.pop();
			ll old_phi = ver.first;
			int v = ver.second;
			if (old_phi != phi[v]) continue;
			for (int i = 0; i < g[v].size(); i++) {
				Edge& e = g[v][i];
				int u = e.to;
				if (e.cap <= e.flow) continue;
				if (phi[u] > phi[v] + e.cost + dis[v] - dis[u]) {
					phi[u] = phi[v] + e.cost + dis[v] - dis[u];
					q.push({phi[u], u});
					par[u] = {v, i};
					flo[u] = min(flo[v], e.cap - e.flow);
				}
			}
		}
		if (phi[sink] == inf) break;
		for (int i = 0; i < N; i++) {
			if (phi[i] < inf) {
				dis[i] += phi[i];
			}
		}
		ll f = min(flo[sink], bound - flow);
        if (!f) break;
		flow += f;
		int v = sink;
		while (v != src) {
			Edge& e = g[par[v].first][par[v].second];
			e.flow += f;
			g[v][e.rev].flow -= f;
			cost += f * e.cost;
			v = par[v].first;
		}
	}
	return {flow, cost};
}

int main() {
    return 0;
}
