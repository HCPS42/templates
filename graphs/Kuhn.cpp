#include <bits/stdc++.h>
using namespace std;

// O(nm)

const int N = 505;

vector<int> g[N];
int lef[N];
int rig[N];
bool used[N];

bool dfs(int v) {
	used[v] = 1;
	for (int u : g[v]) {
		if (lef[u] != v) {
			bool ok;
			if (!lef[u]) ok = 1;
			else if (!used[lef[u]]) {
				ok = dfs(lef[u]);
			}
			else ok = 0;
			if (ok) {
				rig[v] = u;
				lef[u] = v;
				return 1;
			}
		}
	}
	return 0;
}

int Kuhn(int n) {
	int res = 0;
	for (int i=1; i<=n; i++) {
		for (int i=1; i<=n; i++) {
			used[i] = 0;
		}
		res += dfs(i);
	}
	return res;
}

int main() {
	return 0;
}
