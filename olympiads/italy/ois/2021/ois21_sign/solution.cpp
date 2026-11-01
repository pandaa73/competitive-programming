#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

void solve(void) {
    ll a, b; cin >> a >> b;

    if(a > 0) {
        cout << "+" << lf;
        return;
    }

    if(a <= 0 && b >= 0) {
        cout << "0" << lf;
        return;
    }

    int k = b - a + 1;
    if(k&1) cout << "-" << lf;
    else cout << "+" << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--) solve();
}