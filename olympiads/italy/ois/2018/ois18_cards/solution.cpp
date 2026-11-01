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

    int sussone_epico_che_serve_tantissimo; cin >> sussone_epico_che_serve_tantissimo;
    ll n, m; cin >> n >> m;

    ll l = m - 1, r = n - m;
    
    cout << (n * (n + 1) / 2) - (l * (l + 1) / 2) - (r * (r + 1) / 2) << lf;
}