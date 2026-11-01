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

    int n; cin >> n;

    auto calc = [&](ll x) -> ll {
        ll e = 64 - __builtin_clzll(x);

        return (1LL << e) - x - 1;
    };

    ll ans = 0, x;
    while(n--) cin >> x, ans += calc(x);

    cout << ans << lf;
}
