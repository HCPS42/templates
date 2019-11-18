#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int, int>
#define fi first
#define se second

struct CHT {
	int pointer=0;
	vector<ll> K, B;
	void clear() {
		pointer = 0;
		K.clear();
		B.clear();
	}
	bool bad(int l1, int l2, int l3) {
		return (B[l3]-B[l1])*(K[l1]-K[l2])<(B[l2]-B[l1])*(K[l1]-K[l3]);
	}
	void add(ll k, ll b) {
		if (!K.empty() && K.back() == k) return;
		K.pb(k);
		B.pb(b);
		while (K.size() >= 3 && bad(K.size()-3, K.size()-2, K.size()-1)) {
			K.erase(K.end()-2);
			B.erase(B.end()-2);
		}
	}
	ll getmin(ll x) {
		while (pointer < K.size()-1 && K[pointer+1] * x + B[pointer+1] < K[pointer] * x + B[pointer]) pointer++;
		return K[pointer] * x + B[pointer];
	}
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    
    return 0;
}
