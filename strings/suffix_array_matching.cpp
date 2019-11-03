#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second

const int N = 2e5 + 5;

int order[N], cnt[N], cls[N], new_order[N], new_cls[N];
string s;
int n;
bool ans[N];

int tr(char c) {
    if (c == '$') return 0;
    else return c - 'a' + 1;
}

void sort_char() {
    for (int i=0; i<27; i++) cnt[i] = 0;
    for (int i=0; i<n; i++) cnt[tr(s[i])]++;
    for (int i=1; i<27; i++) cnt[i] += cnt[i-1];
    for (int i=n-1; i>=0; i--) order[--cnt[tr(s[i])]] = i;
}

void calc_char_cls() {
    cls[order[0]] = 0;
    for (int i=1; i<n; i++) {
        if (s[order[i]] != s[order[i-1]]) cls[order[i]] = cls[order[i-1]] + 1;
        else cls[order[i]] = cls[order[i-1]];
    }
}

void sort_doubled(int k) {
    for (int i=0; i<n; i++) cnt[i] = 0;
    for (int i=0; i<n; i++) cnt[cls[i]]++;
    for (int i=1; i<n; i++) cnt[i] += cnt[i-1];
    for (int i=n-1; i>=0; i--) {
        int start = (order[i] - k + n) % n;
        new_order[--cnt[cls[start]]] = start;
    }
}

void upd_cls(int k) {
    new_cls[new_order[0]] = 0;
    for (int i=1; i<n; i++) {
        int cur = new_order[i];
        int prev = new_order[i-1];
        int mid = (cur + k) % n;
        int mid_prev = (prev + k) % n;
        if (cls[cur] != cls[prev] || cls[mid] != cls[mid_prev]) {
            new_cls[cur] = new_cls[prev] + 1;
        }
        else new_cls[cur] = new_cls[prev];
    }
}

void calc_suff_array() {
    sort_char();
    calc_char_cls();
    int n = s.length();
    int k = 1;
    while (k < n) {
        sort_doubled(k);
        upd_cls(k);
        for (int i=0; i<n; i++) {
            order[i] = new_order[i];
            cls[i] = new_cls[i];
        }
        k *= 2;
    }
}

inline bool operator>(string &p, int &k) {
    int cur = 0;
    while (cur < p.length() && p[cur] == s[k + cur]) cur++;
    if (cur == p.length()) return 0;
    else if (p[cur] > s[k + cur]) return 1;
    else return 0;
}

inline bool operator<(string &p, int &k) {
    int cur = 0;
    while (cur < p.length() && p[cur] == s[k + cur]) cur++;
    if (cur == p.length()) return 0;
    else return 1;
}

void search(string &p) {
    int l = 0, r = n;
    while (l < r) {
        int mid = (l + r) / 2;
        if (p > order[mid]) l = mid + 1;
        else r = mid;
    }
    int lo = l;
    r = n;
    while (l < r) {
        int mid = (l + r) / 2;
        if (p < order[mid]) r = mid;
        else l = mid + 1;
    }
    int hi = r-1;
    for (int i=lo; i<=hi; i++) ans[order[i]] = 1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    cin >> s;
    s += '$';
    n = s.length();
    calc_suff_array();
    for (int i=0; i<n; i++) ans[i] = 0;
    int t;
    cin >> t;
    for (int q=1; q<=t; q++) {
        string pattern;
        cin >> pattern;
        search(pattern);
    }
    for (int i=0; i<n; i++) {
        if (ans[i]) cout << i << " ";
    }
    cout << "\n";
    return 0;
}
