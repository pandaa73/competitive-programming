#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

using ll = long long;

int count_sets(int N, vector<int> U, vector<int> V) {
    vector<vector<int>> adj(N);
    for(int i = 0; i < U.size(); ++i) {
        adj[U[i]].push_back(V[i]);
        adj[V[i]].push_back(U[i]);
    }

    vector<array<ll, 2>> dp(N, {1, 0});
    auto dfs = [&](int v, int f, auto &&dfs) -> void {
        for(auto u: adj[v]) {
            if(u == f) continue;

            dfs(u, v, dfs);

            dp[v][0] *= 1 + dp[u][0];
            dp[v][1] += dp[u][0] + dp[u][1];

            dp[v][0] %= MOD, dp[v][1] %= MOD;
        }
    };

    dfs(0, -1, dfs);

    return (dp[0][0] + dp[0][1]) % MOD;
}
