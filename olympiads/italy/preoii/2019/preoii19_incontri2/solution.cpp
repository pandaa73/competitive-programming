#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

bool visita(int n, int a[]) {
    int l = 0, r = n - 1;
    ll sl = 0, sr = 0;
    while(r >= l) {
        if(sl == sr) {
            if(l == r) return 1;

            sl += a[l++], sr += a[r--];
        } else if(sl < sr) 
            sl += a[l++];
        else sr += a[r--];
    }

    return 0;
}