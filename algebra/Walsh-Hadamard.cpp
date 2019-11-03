#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define fi first
#define se second
#define pii pair<int,int>
#define div divi

const int N = 1 << 17;
const ll p = 1e9 + 7;

ll add(ll a, ll b) {
	a += b;
	if (a >= p) a -= p;
	return a;
}

ll sub(ll a, ll b) {
	a -= b;
	if (a < 0) a += p;
	return a;
}

ll mult(ll a, ll b) {
	return (a * b) % p;
}

ll binpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b & 1) res = mult(res, a);
		b >>= 1;
		a = mult(a, a);
	}
	return res;
}

ll div(ll a, ll b) {
	return mult(a, binpow(b, p-2));
}

void reduce(ll &a) {
	a %= p;
	if (a < 0) a += p;
}

void tr_xor(ll *from, ll *to) {
	if (to - from == 1) return;
	ll *mid = from + (to - from) / 2;
	tr_xor(from, mid);
	tr_xor(mid, to);
	for (int i=0; i<mid-from; i++) {
		ll a = *(from + i);
		ll b = *(mid + i);
		*(from + i) = add(a, b);
		*(mid + i) = sub(a, b);
	}
}

void inv_xor(ll *from, ll *to) {
	tr_xor(from, to);
	int n = to - from;
	ll inv_n = div(1, n);
	for (int i=0; i<n; i++) {
		*(from + i) = mult(*(from + i), inv_n);
	}
}

void conv_xor(ll *from1, ll *to1, ll *from2, ll *to2) {
	tr_xor(from1, to1);
	tr_xor(from2, to2);
	int n = to1 - from1;
	for (int i=0; i<n; i++) {
		*(from1 + i) = mult(*(from1 + i), *(from2 + i));
	}
	inv_xor(from1, to1);
	inv_xor(from2, to2);
	for (int i=0; i<n; i++) {
		reduce(*(from1 + i));
	}
}

void tr_or(ll *from, ll *to) {
	if (to - from == 1) return;
	ll *mid = from + (to - from) / 2;
	tr_or(from, mid);
	tr_or(mid, to);
	for (int i=0; i<mid-from; i++) {
		*(mid + i) = add(*(mid + i), *(from + i));
	}
}

void inv_or(ll *from, ll *to) {
	if (to - from == 1) return;
	ll *mid = from + (to - from) / 2;
	for (int i=0; i<mid-from; i++) {
		*(mid + i) = sub(*(mid + i), *(from + i));
	}
	inv_or(from, mid);
	inv_or(mid, to);
}

void conv_or(ll *from1, ll *to1, ll *from2, ll *to2) {
	tr_or(from1, to1);
	tr_or(from2, to2);
	int n = to1 - from1;
	for (int i=0; i<n; i++) {
		*(from1 + i) = mult(*(from1 + i), *(from2 + i));
	}
	inv_or(from1, to1);
	inv_or(from2, to2);
	for (int i=0; i<n; i++) {
		reduce(*(from1 + i));
	}
}

void conv_and(ll *from1, ll *to1, ll *from2, ll *to2) {
	int n = to1 - from1;
	int mask = n - 1;
	for (int i=0; i<n/2; i++) {
		swap(*(from1 + i), *(from1 + (i ^ mask)));
		swap(*(from2 + i), *(from2 + (i ^ mask)));
	}
	conv_or(from1, to1, from2, to2);
	for (int i=0; i<n/2; i++) {
		swap(*(from1 + i), *(from1 + (i ^ mask)));
		swap(*(from2 + i), *(from2 + (i ^ mask)));
	}
	for (int i=0; i<n; i++) {
		reduce(*(from1 + i));
	}
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
	
	return 0;
}
