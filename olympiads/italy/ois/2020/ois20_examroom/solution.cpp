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

    ll n, m, k; cin >> n >> m >> k;

    n = n / k + (bool)(n % k);
    m = m / k + (bool)(m % k);

    cout << n * m << lf;
}