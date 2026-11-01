#include <bits/stdc++.h>
using namespace std;

/* ඞඞ flag[10] ඞඞ */

#define ff endl
#define lf "\n"
#define _ << " " <<

using ll = long long;

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

void solve(void) {
    ll n, m, k; cin >> n >> m >> k;

    // for(ll i = 0; i < k; ++i) {
    //     if(n > m) n--;
    //     else m--;
    // }

    ll diff = abs(n-m);
    if(k < diff) {
        cout << (max(n, m)-k)*min(n, m);
        return;
    }

    if(n > m) n -= diff;
    else m -= diff;

    k -= diff;

    if(k == 0) {
        cout << n*m;
        return;
    }

    n -= k/2;
    k -= k/2;
    m -= k;

    // Case #3: 4414201
    // Case #1: 615600

    cout << n*m;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t; cin >> t;
    for(int i = 1; i <= t; ++i)
        cout << "Case #" << i << ": ", solve(), cout << lf;
}