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
    ll p[n]; for(auto &x: p) cin >> x;
    ll v[n]; for(auto &x: v) cin >> x;

    ll mn = p[0], sum = p[0] * v[0];
    for(int i = 1; i < n; ++i) {
        mn = min(mn, p[i]);

        sum += mn * v[i];
    }

    cout << sum << lf;
}