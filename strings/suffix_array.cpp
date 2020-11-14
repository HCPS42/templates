#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int order[N];
int cnt[N];
int cls[N];
int new_order[N];
int new_cls[N];

int tr(char c) {
    if (c == '$') return 0;
    return c - 'a' + 1;
}

void sort_char(string s) {
    int n = s.length();
    for (int i = 0; i < 27; i++) {
        cnt[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        cnt[tr(s[i])]++;
    }
    for (int i = 1; i < 27; i++) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        order[--cnt[tr(s[i])]] = i;
    }
}

void calc_char_cls(string s) {
    int n = s.length();
    cls[order[0]] = 0;
    for (int i = 1; i < n; i++) {
        if (s[order[i]] != s[order[i - 1]]) {
            cls[order[i]] = cls[order[i - 1]] + 1;
        }
        else {
            cls[order[i]] = cls[order[i - 1]];
        }
    }
}

void sort_doubled(string s, int k) {
    int n = s.length();
    for (int i = 0; i < n; i++) {
        cnt[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        cnt[cls[i]]++;
    }
    for (int i = 1; i < n; i++) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        int start = (order[i] - k + n) % n;
        new_order[--cnt[cls[start]]] = start;
    }
}

void upd_cls(int k, int n) {
    new_cls[new_order[0]] = 0;
    for (int i = 1; i < n; i++) {
        int cur = new_order[i];
        int prev = new_order[i - 1];
        int mid = (cur + k) % n;
        int mid_prev = (prev + k) % n;
        if (cls[cur] != cls[prev] || cls[mid] != cls[mid_prev]) {
            new_cls[cur] = new_cls[prev] + 1;
        }
        else {
            new_cls[cur] = new_cls[prev];
        }
    }
}

void build_suff_array(string s) {
    sort_char(s);
    calc_char_cls(s);
    int n = s.length();
    int k = 1;
    while (k < n) {
        sort_doubled(s, k);
        upd_cls(k, n);
        for (int i = 0; i < n; i++) {
            order[i] = new_order[i];
            cls[i] = new_cls[i];
        }
        k *= 2;
    }
}

int main() {
    string text;
    cin >> text;
    text += '$';
    build_suff_array(text);
    int n = text.length();
    for (int i = 0; i < n; i++){
        cout << order[i] << " ";
    }
    cout << "\n";
    return 0;
}
