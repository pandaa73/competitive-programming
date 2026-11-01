#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

ll aggiorna(int n, vector<int> a, vector<int> b) {
    ll cnt = 0;
    for(int i = n - 2; i >= 0; i--) {
        int k = (a[i + 1] - a[i]) / b[i];

        cnt += k; a[i] += b[i] * k;
    }

    return cnt;
}