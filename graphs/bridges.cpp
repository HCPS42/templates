#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second

const int N = 2e4 + 5;

vector<pii> g[N];
bool used[N];
int tin[N];
int dp[N];
int timer = 0;
vector<int> bridges;

void dfs(int v = 1, int par = 0) {
	used[v] = 1;
	tin[v] = dp[v] = timer++;
	for (pii e : g[v]) {
		int u = e.fi;
		int id = e.se;
		if (u == par) continue;
		if (used[u]) {
			dp[v] = min(dp[v], tin[u]);
			continue;
		}
		dfs(u, v);
		dp[v] = min(dp[v], dp[u]);
		if (dp[u] > tin[v]) {
			bridges.pb(id);
		}
	}
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	
	return 0;
}
