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

    ll n; cin >> n;

    ll l = 1, r = INT_MAX;
    while(r - l > 1LL) {
        ll m = (l + r) / 2LL;

        if((m * (m + 1)) / 2LL > n)
            r = m;
        else l = m;
    }

    cout << l << lf;
}