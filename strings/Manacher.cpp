#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int, int>
#define fi first
#define se second

vector<int> d1;
vector<int> d2;

void manacher(string s) {
	int n = s.size();
	d1.resize(n);
	for (int i = 0, l = 0, r = -1; i < n; i++) {
		int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
		while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
			k++;
		}
		d1[i] = k--;
		if (i + k > r) {
			l = i - k;
			r = i + k;
		}
	}
	d2.resize(n);
	for (int i = 0, l = 0, r = -1; i < n; i++) {
		int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
		while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
			k++;
		}
		d2[i] = k--;
		if (i + k > r) {
			l = i - k - 1;
			r = i + k ;
		}
	}
}

void Solve() {
	
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	Solve();
	return 0;
}
