#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef __int128 LL;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second
#define stie std::tie
#define F first
#define S second

template<class T> void mini(T& a, T b) { a = min(a, b); }
template<class T> void maxi(T& a, T b) { a = max(a, b); }
template<class T1, class T2> ostream& operator<<(ostream &out, pair<T1, T2> a) { return out << a.first << " " << a.second; }
template<class T> ostream& operator<<(ostream& out, vector<T> a) { for (auto& i : a) out << i << " "; return out; }
template<class T> ostream& operator<<(ostream& out, set<T> a) { for (auto& i : a) out << i << " "; return out; }
template<class T> ostream& operator<<(ostream& out, multiset<T> a) { for (auto& i : a) out << i << " "; return out; }
template<class T1, class T2> ostream& operator<<(ostream& out, map<T1, T2> a) { for (auto& i : a) out << i << " "; return out; }
template<class T1, class T2> ostream& operator<<(ostream& out, unordered_map<T1, T2> a) { for (auto& i : a) out << i << " "; return out; }
template<class T> ostream& operator<<(ostream& out, queue<T> a) { while (!a.empty()) { cout << a.front() << " "; a.pop(); } return out; }
template<class T> ostream& operator<<(ostream& out, deque<T> a) { while (!a.empty()) { cout << a.front() << " "; a.pop_front(); } return out; }
template<class T> void out(T a) { cout << a << endl; }
void out() { cout << "OK" << endl; }
istream& operator>>(istream& in, __int128& a) { int64_t b; cin >> b; a = b; return in; }
ostream& operator<<(ostream& out, const __int128 a) {
	unsigned __int128 b = a < 0 ? -a : a; char buf[128]; char* c = end(buf); do { --c; *c = "0123456789"[b % 10]; b /= 10; } while (b);
	if (a < 0) { --c; *c = '-'; } int len = end(buf) - c; out.rdbuf()->sputn(c, len); return out;
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
