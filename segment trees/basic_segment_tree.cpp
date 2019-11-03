#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second

const int N = 1e6 + 5;
const int K = 1 << int(ceil(log2(N)));

ll a[N], t[2*K];

void build() {
	for (int i=1; i<N; i++) t[i+K-1] = a[i];
	for (int i=K-1; i>=1; i--) t[i] = t[i+i] + t[i+i+1];
}

void upd(int id, ll x) {
	id += K-1;
	while (id) {
		t[id] += x;
		id /= 2;
	}
}

ll get(int l, int r) {
	l += K-1;
	r += K-1;
	ll res = 0;
	while (l <= r) {
		if (l % 2 == 1) res += t[l++];
		if (r % 2 == 0) res += t[r--];
		l /= 2;
		r /= 2;
	}
	return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
	
    return 0;
}
