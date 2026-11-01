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

    ll a, b, x; cin >> a >> b >> x;

    ll k = a + 24 - b;
    x -= 24 - b;

    ll l = x / 24, m = x % 24;

    x -= l * k;

    if(m > b) x -= m - b;
    if(m > a) x -= a;
    else x -= m;

    cout << x << lf;
}