#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define fi first
#define se second
#define pii pair<int,int>

const int N = 1e5 + 5;
const int K = 18;

int log_2[N];
int st[N][K];
int a[N];

void precalc() {
	for (int i=2; i<N; i++) {
		log_2[i] = log_2[i/2] + 1;
	}
	for (int i=0; i<N; i++) {
		st[i][0] = a[i];
	}
	for (int j=1; j<K; j++) {
		for (int i=0; i + (1 << j) < N; i++) {
			st[i][j] = min(st[i][j-1], st[i + (1 << (j-1))][j-1]);
		}
	}
}

int get_min(int l, int r) {
	int j = log_2[r - l + 1];
	return min(st[l][j], st[r - (1 << j) + 1][j]);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
	// read
	precalc();
	return 0;
}
