#include <bits/stdc++.h>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second

const int N = 2e5 + 5;

int order[N], cnt[N], cls[N], new_order[N], new_cls[N];
int lcp[N], id_to_order[N];
vector<pii> ans;

int tr(char c) {
    if (c == '$') return 0;
    else return c - 'a' + 1;
}

void sort_char(string &s) {
    int n = s.length();
    for (int i=0; i<27; i++) cnt[i] = 0;
    for (int i=0; i<n; i++) cnt[tr(s[i])]++;
    for (int i=1; i<27; i++) cnt[i] += cnt[i-1];
    for (int i=n-1; i>=0; i--) order[--cnt[tr(s[i])]] = i;
}

void calc_char_cls(string &s) {
    int n = s.length();
    cls[order[0]] = 0;
    for (int i=1; i<n; i++) {
        if (s[order[i]] != s[order[i-1]]) cls[order[i]] = cls[order[i-1]] + 1;
        else cls[order[i]] = cls[order[i-1]];
    }
}

void sort_doubled(string &s, int k) {
    int n = s.length();
    for (int i=0; i<n; i++) cnt[i] = 0;
    for (int i=0; i<n; i++) cnt[cls[i]]++;
    for (int i=1; i<n; i++) cnt[i] += cnt[i-1];
    for (int i=n-1; i>=0; i--) {
        int start = (order[i] - k + n) % n;
        new_order[--cnt[cls[start]]] = start;
    }
}

void upd_cls(int k, int n) {
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

void build_suff_array(string &s) {
    sort_char(s);
    calc_char_cls(s);
    int n = s.length();
    int k = 1;
    while (k < n) {
        sort_doubled(s, k);
        upd_cls(k, n);
        for (int i=0; i<n; i++) {
            order[i] = new_order[i];
            cls[i] = new_cls[i];
        }
        k *= 2;
    }
}

void build_lcp_array(string s) {
    int n = s.length();
    for (int i=0; i<n; i++) id_to_order[order[i]] = i;
    int id = 0, cur = 0;
    while (id + 1 < n) {
        int i = id_to_order[id];
        if (i + 1 < n) {
            while (s[order[i] + cur] == s[order[i+1] + cur]) cur++;
        }
        lcp[i] = cur;
        cur = max(cur-1, 0);
        id++;
    }
}

struct Node {
    Node *next[27];
    Node *parent;
    int start, end;
    Node(int start_, int end_) {
        for (int i=0; i<27; i++) next[i] = NULL;
        parent = NULL;
        start = start_;
        end = end_;
    }
};

Node *root;

void build_suffix_tree(string s) {
    int n = s.length();
    root = new Node(-1, -1);
    int id = 0;
    Node *v = root;
    while (1) {
        Node *u;
        int l = order[id], r = n;
        if (id == 0) {
            u = new Node(l, r);
            v->next[tr(s[l])] = u;
        }
        else {
            u = new Node(l + lcp[id-1], r);
            v->next[tr(s[l + lcp[id-1]])] = u;
        }
        u->parent = v;
        v = u;
        if (id == n-1) break;
        int cur = n - order[id];
        while (cur > lcp[id]) {
            cur -= v->end - v->start;
            v = v->parent;
        }
        if (cur < lcp[id]) {
            u = v->next[tr(s[l + cur])];
            Node *w = new Node(u->start, u->start + lcp[id] - cur);
            u->parent = w;
            u->start += lcp[id] - cur;
            v->next[tr(s[l + cur])] = w;
            w->parent = v;
            w->next[tr(s[u->start])] = u;
            v = w;
        }
        id++;
    }
}

void dfs(Node *v) {
    if (v->start != -1) ans.pb({v->start, v->end});
    for (int i=0; i<27; i++) {
        if (v->next[i] != NULL) dfs(v->next[i]);
    }
}

int main_with_large_stack_space() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    string text;
    cin >> text;
    build_suff_array(text);
    build_lcp_array(text);
    build_suffix_tree(text);
    dfs(root);
    cout << text << "\n";
    for (pii edge : ans) {
        cout << edge.fi << " " << edge.se << "\n";
    }
    return 0;
}

int main() {
#if defined(__unix__) || defined(__APPLE__)
  const rlim_t kStackSize = 16 * 1024 * 1024;
  struct rlimit rl;
  int result;
  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0) {
      if (rl.rlim_cur < kStackSize) {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0) cerr << "setrlimit returned result = " << result << "\n";
      }
  }
#endif
    return main_with_large_stack_space();
}
