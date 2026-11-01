#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

using ll = long long;

void solve(void) {
    int N; cin >> N;
    vector<int> v(N);
    for(auto &x: v) cin >> x;

    int ans = v[0];
    for(int i = 1; i < N; ++i) {
        if(v[i] <= v[i - 1]) continue;

        ans += v[i] - v[i - 1];
    }

    cout << ans << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t; cin >> t;
    for(int i = 1; i <= t; ++i)
        cout << "Case #" << i << ": ", solve();
}
