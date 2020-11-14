#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
map<pair<int, int>, ll> wei;

bool relax(Edge& e) {
    int u = e.u;
    int v = e.v;
    ll w = e.w;
    if (dist[u] < inf && dist[v] > -inf && dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        return 1;
    }
    return 0;
}

void bellman_ford(int n) {
    for (int i = 1; i <= n - 1; i++) {
        for (Edge& e : edges) {
            relax(e);
        }
    }
}

void reachable_from_negative_cycles() {
    for (Edge& e : edges) {
        if (relax(e)) reachable.push_back(e.v);
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
    int n, m, start;
    cin >> n >> m >> start;
    for (int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        if (wei.count({u, v})) {
            wei[{u, v}] = min(wei[{u, v}], w);
        }
        else {
            wei[{u, v}] = w;
            edges.push_back({u, v, w});
            g[u].push_back(v);
        }
    }
    for (Edge& e : edges) {
        e.w = wei[{e.u, e.v}];
    }
    for (int i = 1; i <= n; i++) {
        dist[i] = inf;
    }
    dist[start] = 0;
    bellman_ford(n);
    reachable_from_negative_cycles();
    for (int v : reachable) {
        if (!used[v]) dfs(v);
    }
    for (int i = 1; i <= n; i++) {
        if (dist[i] == inf) cout << "*\n";
        else if (dist[i] == -inf) cout << "-\n";
        else cout << dist[i] << "\n";
    }
    return 0;
}
