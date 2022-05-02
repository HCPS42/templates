#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 5;

int pref[N];
vector<int> ans;

void prefix_function(string s) {
    int n = s.size();
    pref[0] = 0;
    int bord = 0;
    for (int i = 1; i < n; i++) {
        while (bord > 0 && s[i] != s[bord]) border = pref[bord - 1];
        if (s[i] == s[bord]) bord++;
        else bord = 0;
        pref[i] = bord;
    }
}

void kmp(string pattern, string text) {
    string s = pattern + "$" + text;
    prefix_function(s);
    int k = pattern.size();
    for (int i = k + 1; i < s.size(); i++) {
        if (pref[i] == k) ans.push_back(i - 2 * k);
    }
}

int main() {
    string pattern;
    string text;
    cin >> pattern >> text;
    kmp(pattern, text);
    for (int i : ans) cout << i << " ";
    cout << "\n";
    return 0;
}
