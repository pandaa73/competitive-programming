#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

void solve(void) {
    ll a, b, k; cin >> a >> b >> k;

    ll sum = a + b + k;
    if(a > b) swap(a, b);

    auto check = [&](ll d) -> bool {
        if(d < a) d *= (a / d) + 1;

        ll x = d - a;
        if(x <= k && sum - d == b + (k - x))
            return 1;

        return 0;
    };

    ll mx = 1;
    for(ll  d = 1; d * d <= sum; ++d) {
        if(sum % d) continue;

        ll x = sum / d;

        if(check(d)) mx = max(mx, d);
        if(check(x)) mx = max(mx, x);
    }

    cout << mx << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--) solve();
}
