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
    ll n; cin >> n;

    ll log = 0;
    ll k = n;
    while(k > 0) ++log, k >>= 1;
    ll pow = (1LL << log);

    if(n == pow/2) {
        cout << log-1;
        return;
    }

    ll diff = pow - n;

    ll cnt = 0;
    for(int i = 0; i < 64; ++i) {
        cnt += (diff&1);
        diff >>= 1;
    }

    cout << log + cnt;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t; cin >> t;
    for(int i = 1; i <= t; ++i)
        cout << "Case #" << i << ": ", solve(), cout << lf;
}