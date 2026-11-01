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
    int v[n]; for(auto &x: v) cin >> x;

    sort(v, v+n, [&](const int& a, const int &b) {
        return a > b;
    });

    int sum = 0;
    for(int i = 0; i < n; ++i) {
        if(i%3 == 2) continue;

        sum += v[i];
    }

    cout << sum << lf;
}