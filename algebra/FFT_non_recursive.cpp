#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second

//https://habr.com/ru/post/113642/

typedef complex<double> C;
typedef vector<C> poly_C;
typedef vector<ll> poly;
const double pi = acos(-1);

const int K = 1 << 22;
C w[K];
int index[K];

void init(int n) {
	for (int i=0; i<n; i++) {
		w[i] = polar(1.0, 2 * pi * i / n);
	}
	int k = 0;
    while ((1 << k) < n) k++;
    index[0] = 0;
    int high1 = -1;
    for (int i=1; i<n; i++) {
       if ((i & (i - 1)) == 0) high1++;
       index[i] = index[i ^ (1 << high1)];
       index[i] |= (1 << (k - high1 - 1));
    }
}

poly_C fft(const poly_C& a) {
    int n = a.size();
    poly_C cur(n), nw_cur(n);
    for (int i=0; i<n; i++) {
        cur[i] = a[index[i]];
    }
    for (int len=1; len<n; len*=2) {
        int rig_step = n / (len * 2);
        int ptr_dest = 0;
        while (ptr_dest < n) {
            for (int i=0; i<len; i++) {
                C val = w[i * rig_step] * cur[ptr_dest + len];
                nw_cur[ptr_dest] = cur[ptr_dest] + val;
                nw_cur[ptr_dest + len] = cur[ptr_dest] - val;
                ptr_dest++;
            }
            ptr_dest += len;
        }
        swap(cur, nw_cur);
    }
    return cur;
}

poly_C inter(const poly_C& a) {
    int n = a.size();
    poly_C res = fft(a);
    for (int i=0; i<n; i++) {
        res[i] /= n;
    }
    reverse(res.begin() + 1, res.end());
    return res;
}

void align(poly_C& a, poly_C& b) {
    int n = a.size() + b.size() - 1;
    while (__builtin_popcount(n) != 1) n++;
    while (a.size() < n) a.pb(0);
    while (b.size() < n) b.pb(0);
}

poly mult(poly a, poly b) {
	poly_C A(a.size()), B(b.size());
	for (int i=0; i<a.size(); i++) A[i] = a[i];
	for (int i=0; i<b.size(); i++) B[i] = b[i];
	align(A, B);
	int n = A.size();
	init(n);
	A = fft(A);
	B = fft(B);
	for (int i=0; i<n; i++) A[i] *= B[i];
	A = inter(A);
	poly res(n);
	for (int i=0; i<n; i++) res[i] = round(real(A[i]));
	return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
	
	return 0;
}
