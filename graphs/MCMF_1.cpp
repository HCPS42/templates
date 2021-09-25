#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/contest/1510/problem/B
// https://official.contest.yandex.com/ptz-summer-2020/contest/19423/problems/E3

typedef long long ll;

const int N = 2105;
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

int a[N];
int to[N];
int from[N];
vector<int> st;
vector<int> ans;
int d;

void go(int x) {
    for (int i = 0; i < d; i++) {
        if (x & (1 << i)) {
            ans.push_back(i);
        }
    }
}

int main() {
    int n;
    cin >> d >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < d; j++) {
            if (s[j] == '1') {
                a[i] |= 1 << j;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            if ((a[i] & a[j]) == a[i]) {
                add_edge(i, j + n, 1, 0);
            }
        }
    }
    int src = 0;
    int sink = 2 * n + 1;
    for (int i = 1; i <= n; i++) {
        add_edge(src, i, 1, - __builtin_popcount(a[i]) - 1);
    }
    for (int i = n + 1; i <= 2 * n; i++) {
        add_edge(i, sink, 1, 0);
    }
    min_cost_max_flow(src, sink);
    for (auto e : edges) {
        int u = e.s;
        int v = e.e;
        int flow = e.flow;
        if (1 <= u && u <= n && n + 1 <= v && v <= 2 * n && flow > 0) {
            to[u] = v - n;
            from[v - n] = u;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (from[i] == 0) {
            st.push_back(i);
        }
    }
    for (int i = 0; i < st.size(); i++) {
        int v = st[i];
        go(a[v]);
        while (to[v]) {
            go(a[to[v]] ^ a[v]);
            v = to[v];
        }
        if (i + 1 < st.size()) {
            ans.push_back(-1);
        }
    }
    cout << ans.size() << "\n";
    for (int i : ans) {
        if (i == -1) {
            cout << "R ";
        }
        else {
            cout << i << " ";
        }
    }
    cout << "\n";
    return 0;
}
