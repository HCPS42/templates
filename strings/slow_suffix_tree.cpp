#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define fi first
#define se second
#define pii pair<int,int>

unordered_map<char, int> f;

struct Node {
    int l, r, start;
    Node *next[27];
    bool good;
    Node(int l_, int r_, int start_) {
        l = l_;
        r = r_;
        start = start_;
        for (int i=0; i<=26; i++) next[i] = NULL;
        good = false;
    }
};

void prep() {
    for (int i=0; i<=25; i++) f['a' + i] = i;
    f['$'] = 26;
}

void build_suff_tree(Node *&root, string text) {
    root = new Node(-1, -1, -1);
    int n = text.length();
    for (int i=0; i<n; i++) {
        Node *v = root;
        int j = i;
        while (j < n) {
            if (v->next[f[text[j]]] == NULL) {
                v->next[f[text[j]]] = new Node(j, n-1, i);
                break;
            }
            v = v->next[f[text[j]]];
            int l = v->l, r = v->r;
            for (int k=l; k<=r; k++) {
                if (text[k] != text[j]) {
                    Node *u = new Node(k, r, v->start);
                    for (int t=0; t<=26; t++) {
                        u->next[t] = v->next[t];
                        v->next[t] = NULL;
                    }
                    v->r = k-1;
                    v->next[f[text[k]]] = u;
                    v->next[f[text[j]]] = new Node(j, n-1, i);
                    j = n;
                    break;
                }
                j++;
            }
        }
    }
}

void dfs(Node *v, string &text) {
    for (int i=0; i<=26; i++) {
        if (v->next[i] != NULL) {
            for (int j=v->next[i]->l; j<=v->next[i]->r; j++) cout << text[j];
            cout << endl;
            dfs(v->next[i], text);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    prep();
    string text;
    cin >> text;
    text += '$';
    Node *root;
    build_suff_tree(root, text);
    dfs(root, text);
}
