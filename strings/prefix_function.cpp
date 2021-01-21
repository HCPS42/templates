#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 5;

int pref[N];

void prefix_function(string s) {
    int n = s.size();
    pref[0] = 0;
    int bord = 0;
    for (int i = 1; i < n; i++) {
        while (bord > 0 && s[i] != s[bord]) bord = pref[bord - 1];
        if (s[i] == s[bord]) bord++;
        else bord = 0;
        pref[i] = bord;
    }
}

int main() {
    return 0;
}
