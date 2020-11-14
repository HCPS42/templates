#pragma comment(linker, "/STACK:64000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif
using namespace std;

int main_with_large_stack_space() {
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
