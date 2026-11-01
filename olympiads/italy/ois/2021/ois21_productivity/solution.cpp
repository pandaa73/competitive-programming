#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m, e; cin >> n >> m >> e;

    int mx = 0;
    for(int i = m; i <= n; ++i) {
        mx = max(mx, e % i);
    }

    cout << mx << lf;
}