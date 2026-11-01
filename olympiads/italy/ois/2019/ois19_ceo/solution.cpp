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

    ll ans = 1;
    ll mul = 1;
    while(n--) {
        ll x; cin >> x;
        mul *= x;
        ans += mul;
    }

    cout << ans << lf;
}