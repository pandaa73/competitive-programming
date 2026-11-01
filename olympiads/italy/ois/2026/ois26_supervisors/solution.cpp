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

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

template<typename T>
void chmax(T &a, T b) {
    a = max(a, b);
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, K; cin >> N >> K;

    vector<ll> V(N);
    for(auto &x: V) cin >> x;

    vector<vector<int>> adj(N);
    for(int i = 1; i < N; ++i) {
        int f; cin >> f;

        adj[f].emplace_back(i);
    }

    vector dp(N, vector<ll>(K + 2, -1));
    auto dfs = [&](int v, auto &&dfs) -> void {
        ll w = V[v];

        dp[v][1] = 0;
        for(auto u: adj[v]) {
            const auto acc = dp[v];

            dfs(u, dfs);

            for(int k = 1; acc[k] >= 0; ++k) {
                for(int i = 1; i + k <= K; ++i) {
                    if(dp[u][i] < 0) break;

                    chmax(dp[v][i + k], dp[u][i] + acc[k] + w * i * k);
                }
            }

            for(int i = 1; i <= K; ++i) {
                if(dp[u][i] < 0) break;

                chmax(dp[v][i], dp[u][i]);
            }
        }

        infor("dp[%d]:", v);
        for(auto x: dp[v]) {
            if(x < 0) continue;
            infor(" %d", x);
        }

        infof("");
    };

    dfs(0, dfs);

    cout << dp[0][K] << lf;
}
