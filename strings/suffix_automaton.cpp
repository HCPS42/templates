#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int, int>
#define fi first
#define se second

const int N = 2e5 + 5;

int to[N][26];
int link[N];
int len[N];
int first_pos[N];
int nw = 0, sz = 1;

void add_letter(int c) {
	int p = nw;
	nw = sz++;
	len[nw] = len[p] + 1;
	firstpos[nw] = len[nw];
	while (to[p][c] == 0) {
		to[p][c] = nw;
		p = link[p];
	}
	if (to[p][c] == nw) {
		link[nw] = 0;
		return;
	}
	int q = to[p][c];
	if (len[q] == len[p] + 1) {
		link[nw] = q;
		return;
	}
	int cl = sz++;
	len[cl] = len[p] + 1;
	link[cl] = link[q];
	link[nw] = link[q] = cl;
	first_pos[clone] = first_pos[q];
	for (int i=0; i<26; i++) to[cl][i] = to[q][i];
	while (to[p][c] == q) {
		to[p][c] = cl;
		p = link[p];
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif

	return 0;
}