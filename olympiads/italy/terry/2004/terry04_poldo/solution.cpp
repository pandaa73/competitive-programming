#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infos(str) do { fprintf(stderr, str"\n"); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", __VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infos
#undef infof

#define infos(str)
#define infof(str, ...)

#endif

using ll = long long;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
        
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vector<int> V(N);
    for(auto &x: V) cin >> x;

    vector<int> dp(N);
    for(int i = 0; i < N; ++i) {
        dp[i] = 1;

        for(int j = 0; j < i; ++j) {
            if(V[i] >= V[j]) continue;

            dp[i] = max(dp[i], 1 + dp[j]);
        }
    }

    int mx = 0;
    for(auto x: dp)
        mx = max(mx, x);

    cout << mx << lf;
}
