#pragma once

#include <bits/stdc++.h>
using namespace std;

struct perm {
    vector<int> a;
    perm() = default;
    perm(int n) {
        a.resize(n);
        for (int i = 0; i < n; i++) {
            a[i] = i;
        }
    }
    perm(const vector<int>& b) {
        a.resize(b.size());
        for (int i = 0; i < a.size(); i++) {
            a[i] = b[i] - 1;
        }
    }
    int size() const {
        return a.size();
    }
    int& operator[](int i) {
        return a[i];
    }
    const int& operator[](int i) const {
        return a[i];
    }
    perm& operator*=(const perm& b) {
        perm c(a.size());
        for (int i = 0; i < a.size(); i++) {
            c[i] = a[b[i]];
        }
        a = c.a;
        return *this;
    }
    friend perm operator*(perm a, const perm& b) {
        return a *= b;
    }
    friend bool operator==(const perm& a, const perm& b) {
        return a.a == b.a;
    }
    friend ostream& operator<<(ostream& out, const perm& b) {
        for (int i = 0; i < b.size(); i++) {
            cout << i + 1 << " ";
        }
        cout << endl;
        for (int i = 0; i < b.size(); i++) {
            cout << b[i] + 1 << " ";
        }
        cout << endl;
        return out;
    }
    bool next_perm() {
        if (a.size() <= 1) {
            return false;
        }
        int l = 0;
        int r = a.size();
        int i = r - 1;
        while (true) {
            int j = i;
            i--;
            if (a[i] < a[j]) {
                int k = r;
                while (!(a[i] < a[--k]));
                swap(a[i], a[k]);
                reverse(a.begin() + j, a.end());
                return true;
            }
            if (i == l) {
                reverse(a.begin(), a.end());
                return false;
            }
        }
    }
    perm pow(int n) const {
        if (n == 0) {
            return *this;
        }
        if (n == -1) {
            perm b(a.size());
            for (int i = 0; i < a.size(); i++) {
                b[a[i]] = i;
            }
            return b;
        }
        perm b(a.size());
        for (int i = 0; i < n; i++) {
            b *= *this;
        }
        return b;
    }
};
