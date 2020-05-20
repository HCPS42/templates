#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second

template<class T> void mini(T& a, T b) { a = min(a, b); }
template<class T> void maxi(T& a, T b) { a = max(a, b); }
template<class T1, class T2>
ostream& operator<<(ostream &out, pair<T1, T2> a) { return out << "(" << a.fi << ", " << a.se << ")"; }
template<class T> ostream& operator<<(ostream& out, vector<T> a) { out<<"("; for (auto& v : a) out<<v<<", "; return out<<")"; }
template<class T> ostream& operator<<(ostream& out, set<T> a) { out<<"("; for (auto& v : a) out<<v<<", "; return out<<")"; }
template<class L, class R> ostream& operator<<(ostream& out, map<L, R> a) { out<<"("; for (auto& v : a) out<<v<<", "; return out<<")"; }

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
