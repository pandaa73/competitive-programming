#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int MOD = 1e9+7;
constexpr int MAXN = 3e2+7;
constexpr int MAXC = 2e2+7;

using ll = long long;

void solve(void) {
    int N, K; cin >> N >> K;

    int dp[MAXN * MAXC];
    for(auto &x: dp) x = INT_MAX;

    dp[0] = 0;
    for(int i = 0; i < N; ++i) {
        int c, p; cin >> c >> p;

        for(int j = MAXN * MAXC; j >= c; j--) {
            if(dp[j - c] == INT_MAX) continue;

            dp[j] = min(dp[j], dp[j - c] + p);
        }
    }

    int ans = 0;
    for(int i = 0; i < MAXN * MAXC; ++i)
        if(dp[i] <= K) ans = i;

    cout << ans << lf;

}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t; cin >> t;
    for(int i = 1; i <= t; ++i)
        cout << "Case #" << i << ": ", solve();
}
