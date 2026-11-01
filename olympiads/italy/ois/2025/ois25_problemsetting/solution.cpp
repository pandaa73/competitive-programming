#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 2e9+7;
constexpr int MOD = 1e9+7;

using ll = long long;

void solve(void) {
    int n; cin >> n;
    vector<int> a(n), b(n - 1);
    for(auto &x: a) cin >> x;
    for(auto &x: b) cin >> x;

    auto check = [&](ll x) -> bool {
        vector<int> c(b);

        if(a[0] < x) {
            ll d = x - a[0];
            if(c[0] >= d)
                c[0] -= d;
            else return 0;
        }

        for(int i = 1; i < n - 1; ++i) {
            if(a[i] >= x) continue;

            ll d = x - a[i];
            if((ll)(c[i - 1] + c[i]) < d) return 0;
            if(c[i - 1] >= d)
                c[i - 1] -= d;
            else d -= c[i - 1], c[i] -= d;
        }

        if(a[n - 1] < x) {
            ll d = x - a[n - 1];
            if(c[n - 2] >= d)
                return 1;
            else return 0;
        }

        return 1;
    };

    ll l = 0, r = N;
    while(r - l > 1) {
        ll m = (l + r) / 2;

        if(check(m))
            l = m;
        else r = m;
    }

    cout << l << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--) solve();
}
