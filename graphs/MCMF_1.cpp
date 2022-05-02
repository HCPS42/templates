#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/contest/1510/problem/B
// https://official.contest.yandex.com/ptz-summer-2020/contest/19423/problems/E3
// good tests https://codeforces.com/gym/103371/problem/L

// supports negative costs: yes
// supports negative cycles: no

typedef long long ll;

const int N = 2005;
const ll inf = 4e18;

struct Edge {
    int s;
    int e;
    ll cap;
    ll cost;
    ll flow;
};

vector<int> g[N];
vector<Edge> edges;
ll dis[N];
ll phi[N];
int par[N];
bool used[N];

void init_mcmf() {
    for (int i = 0; i < N; i++) {
        g[i].clear();
        dis[i] = 0;
        phi[i] = 0;
        par[i] = 0;
        used[i] = 0;
    }
    edges.clear();
}

void add_edge(int s, int e, ll cap, ll cost) {
    int sz = edges.size();
    edges.push_back({s, e, cap, cost, 0});
    edges.push_back({e, s, 0, -cost, 0});
    g[s].push_back(sz);
    g[e].push_back(sz ^ 1);
}

void bellman_ford(int src) {
    for (int i = 0; i < N; i++) {
        phi[i] = inf;
    }
    phi[src] = 0;
    while (1) { // possibly infinite cycle
        bool relax = 0;
        for (Edge& e : edges) {
            ll nw = phi[e.s] + e.cost;
            if (e.cap > e.flow && phi[e.s] < inf && phi[e.e] > nw) {
                phi[e.e] = nw;
                relax = 1;
            }
        }
        if (!relax) break;
    }
}

bool dijkstra(int src, int sink) {
    for (int i = 0; i < N; i++) {
        dis[i] = inf;
        par[i] = -1;
        used[i] = 0;
    }
    dis[src] = 0;
    priority_queue<pair<ll, int>> q;
    q.push({0, src});
    while (!q.empty()) {
        int v = q.top().second;
        q.pop();
        if (used[v]) continue;
        used[v] = 1;
        for (int i : g[v]) {
            Edge& e = edges[i];
            int u = e.e;
            ll w = e.cost + phi[v] - phi[u];
            if (e.flow < e.cap && dis[u] > dis[v] + w) {
                dis[u] = dis[v] + w;
                par[u] = i;
                q.push({-dis[u], u});
            }
        }
    }
    return par[sink] != -1;
}

pair<ll, ll> min_cost_max_flow(int src, int sink, ll bound = inf) {
    bellman_ford(src);
    ll flow = 0;
    ll cost = 0;
    while (dijkstra(src, sink)) {
        for (int i = 0; i < N; i++) {
            phi[i] += dis[i];
        }
        ll f = bound - flow;
        if (!f) break;
        int v = sink;
        while (v != src) {
            Edge& e = edges[par[v]];
            f = min(f, e.cap - e.flow);
            v = e.s;
        }
        flow += f;
        v = sink;
        while (v != src) {
            Edge& e = edges[par[v]];
            Edge& re = edges[par[v] ^ 1];
            e.flow += f;
            re.flow -= f;
            cost += f * e.cost;
            v = e.s;
        }
    }
    return {flow, cost};
}

int main() {
    return 0;
}
