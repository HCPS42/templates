#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <deque>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <random>
#include <string>
#include <numeric>
#include <complex>
#include <tuple>
#include <utility>
#include <bitset>
#include <array>
#include <stack>
#include <sstream>

using namespace std;
typedef long long ll;
 
string to_string(string a) { return '"' + a + '"'; }
string to_string(char a) { return "'" + string(1, a) + "'"; }
string to_string(const char* a) { return to_string((string) a); }
string to_string(bool a) { return a ? "true" : "false"; }
template <class T1, class T2>
string to_string(pair<T1, T2> a) {
    return "(" + to_string(a.first) + ", " + to_string(a.second) + ")";
}
template <class T>
string to_string(T a) {
    bool first = true; string res = "{";
    for (const auto& i : a) {
        if (!first) res += ", ";
        first = false;
        res += to_string(i);
    }
    res += "}";
    return res;
}
void debug_out() { cerr << endl; }
template <class T1, class... T2>
void debug_out(T1 a, T2... b) {
    cerr << " " << to_string(a);
    debug_out(b...);
}
 
#ifdef LOCAL
#define out(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define out(...) 42
#endif

clock_t start_time; void start_timer() { start_time = clock(); }
double get_time() { return (double) (clock() - start_time) / CLOCKS_PER_SEC; }

void Solve();

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("usr/share/man/man1/input.txt", "r", stdin);
#endif
    start_timer();
    Solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3);
    cerr << endl << "Time spent: " << get_time() << endl;
#endif
    return 0;
}

// do something, stay focused
// look for stupid bugs
// guess, slow, stress
// don't overgeneralize
// don't rush

// don't waste time on standings

// SOLVE THE PROBLEM OR DIE TRYING
// THE SOLUTION IS ALWAYS SIMPLE
// THE CODE IS ALWAYS SHORT

void Solve() {

}
