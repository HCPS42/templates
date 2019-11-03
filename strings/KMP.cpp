#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second

const int N = 2e6 + 5;

int pref[N];
vector<int> ans;

void calc_prefix_array(string s) {
    int n = s.length();
    pref[0] = 0;
    int border = 0;
    for (int i=1; i<n; i++) {
        while (border > 0 && s[i] != s[border]) border = pref[border-1];
        if (s[i] == s[border]) border++;
        else border = 0;
        pref[i] = border;
    }
}

void kmp(string pattern, string text) {
    string s = pattern + '$' + text;
    calc_prefix_array(s);
    int k = pattern.length();
    for (int i=k+1; i<s.length(); i++) {
        if (pref[i] == k) ans.pb(i-2*k);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    string pattern, text;
    cin >> pattern >> text;
    kmp(pattern, text);
    for (int i : ans) cout << i << " ";
    cout << "\n";
    return 0;
}
