#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define fi first
#define se second
#define pii pair<int,int>

const int N = 1e6 + 5;
const ll good_value = 0; // 0 for sum, -inf for max, and inf for min

ll a[N], t[4*N], ch[4*N];

ll merge(ll a, ll b) {
	return a + b;
}

void build(int v=1, int l=0, int r=N-1) {
	if (l == r) {
		t[v] = a[l];
		return;
	}
	int m = (l + r) / 2;
	build(v+v, l, m);
	build(v+v+1, m+1, r);
	t[v] = merge(t[v+v], t[v+v+1]);
}

void push(int v, int l, int r) {
	if (!ch[v]) return;
	t[v] += ch[v] * (r-l+1); // r-l+1 for sum and 1 for min/max
	if (l < r) {
		ch[v+v] += ch[v];
		ch[v+v+1] += ch[v];
	}
	ch[v] = 0;
}

void upd(int L, int R, ll x, int v=1, int l=0, int r=N-1) {
	push(v, l, r);
	if (R < l || r < L) return;
	if (L <= l && r <= R) {
		ch[v] += x;
		push(v, l, r);
		return;
	}
	int m = (l + r) / 2;
	upd(L, R, x, v+v, l, m);
	upd(L, R, x, v+v+1, m+1, r);
	t[v] = merge(t[v+v], t[v+v+1]);
}

ll get(int L, int R, int v=1, int l=0, int r=N-1) {
	push(v, l, r);
	if (R < l || r < L) return good_value;
	if (L <= l && r <= R) return t[v];
	int m = (l + r) / 2;
	ll res = merge(get(L, R, v+v, l, m), get(L, R, v+v+1, m+1, r));
	t[v] = merge(t[v+v], t[v+v+1]);
	return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

	return 0;
}
