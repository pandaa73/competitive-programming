#include <bits/stdc++.h>
using namespace std;

#define ff endl
#define lf "\n"
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#ifdef DEBUG

constexpr bool IS_DEBUG = 1;

#define infor(fmt, ...) do { print(stderr, fmt, ##__VA_ARGS__); } while(0)
#define infof(fmt, ...) do { println(stderr, fmt, ##__VA_ARGS__); } while(0)

#else

constexpr bool IS_DEBUG = 0;

#define infor(fmt, ...)
#define infof(fmt, ...)

#endif

using ll = long long;

#define int ll

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

mt19937 timmy_loves_gambling(73);

constexpr ll INF = 1e18;

signed main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M; cin >> N >> M;

    vec<vec<pii>> adj(N);
    for(int i = 0; i < M; ++i) {
        int u, v, w; cin >> u >> v >> w;
        u -= 1, v -= 1;

        adj[u].emplace_back(v, w);
    }

    vec<ll> dp(N);
    vec<bool> win(N), vis(N);

    auto dfs = [&](int v, auto &&dfs) -> void {
        if(vis[v]) return;
        vis[v] = 1;

        ll a = INF, b = 0;
        for(auto [u, w]: adj[v]) {
            dfs(u, dfs);

            if(!win[u]) {
                win[v] = 1;

                a = min(a, dp[u] + w);
            } else {
                b = max(b, dp[u]);
            }
        }

        dp[v] = win[v] ? a : b;
    };

    dfs(0, dfs);

    infof("win: {}", win);
    infof(" dp: {}", dp);

    cout << (win[0] ? "Alice" : "Bob") << lf;
    cout << dp[0] << lf;
}
