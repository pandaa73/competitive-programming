#include <bits/stdc++.h>
using namespace std;

#define ff endl
#define lf "\n"
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infor(str, ...) do { fprintf(stderr, str, ##__VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", ##__VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infor
#undef infof

#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vector<int> V(N);
    for(auto &x: V) cin >> x;

    vector<vector<int>> adj(N);
    for(int i = 1; i < N; ++i) {
        int j; cin >> j;

        adj[j].push_back(i);
    }

    vector<ll> W(N);
    for(int i = 1; i < N; ++i)
        cin >> W[i];

    vector<array<ll, 2>> dp(N);
    auto dfs = [&](int v, auto &&dfs) -> void {
        ll x = 0;
        vector<ll> d;

        for(auto u: adj[v]) {
            dfs(u, dfs);

            x += dp[u][0];
            d.push_back(dp[u][1] - dp[u][0]);
        }

        sort(rall(d));

        int K = V[v];

        for(int i = 0; i < min((int)d.size(), K - 1); ++i)
            if(d[i] > 0) x += d[i]; else break;

        dp[v][0] = dp[v][1] = x;

        if(K == 0) return;

        dp[v][1] += W[v];
        if(K <= d.size() && d[K - 1] > 0)
            dp[v][0] += d[K - 1];
    };

    dfs(0, dfs);

    cout << dp[0][0] << lf;
}
