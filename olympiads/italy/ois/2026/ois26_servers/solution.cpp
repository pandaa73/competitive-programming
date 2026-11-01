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

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

mt19937 timmy_loves_gambling(73);

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, K; cin >> N >> K;

    vector<vector<int>> adj(N);
    for(int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;

        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> s, t;
    s.reserve(N);
    t.reserve(N);

    vector<int> F(N, -1), sz(N);
    auto dfs = [&](int v, auto &&dfs) -> void {
        sz[v] = adj[v].size() + (v == 0);
        for(auto u: adj[v]) {
            if(u == F[v]) continue;

            F[u] = v;
            dfs(u, dfs);
        }

        if(sz[v] == 1) {
            s.emplace_back(v);
        }
    };

    dfs(0, dfs);

    int d = 0;
    for(; s.size() > K; ++d) {
        for(auto v: s) {
            if(F[v] < 0) continue;

            sz[F[v]] -= 1;
            if(sz[F[v]] == 1) {
                t.emplace_back(F[v]);
            }
        }

        s.clear();
        swap(s, t);
    }

    cout << d << lf;
}
