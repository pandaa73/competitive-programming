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

    if(n == 1) return cout << (!v[0]) << lf, 0;

    auto sx = [&](int idx) {
        if(v[idx] > 0) return;

        if(v[idx - 1] > 1)
            v[idx - 1]--, v[idx]++;
    };

    auto dx = [&](int idx) {
        if(v[idx] > 0) return;

        if(v[idx + 1] > 1)
            v[idx + 1]--, v[idx]++;
    };

    if(v[0] == 0)
        dx(0);

    if(v[n - 1] == 0)
        sx(n - 1);

    for(int i = 1; i < n - 1; ++i)
        sx(i), dx(i);

    int cnt = 0;
    for(auto x: v) cnt += !x;

    cout << cnt << lf;
}