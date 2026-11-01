#include <bits/stdc++.h>
using namespace std;

#define ff endl
#define lf "\n"
#define fi first
#define se second
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

struct MonotonicMap {
    void push(int t, int k) {
        auto it = m.upper_bound(t);

        for(; it != m.end(); it = m.erase(it)) {
            if(it->se > k) break;
        }

        if(it == m.begin() || prev(it)->se < k) m[t] = k;
    }

    map<int, int> m;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, Q; cin >> N >> Q;

    vector<vector<int>> adj(N);
    for(int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;

        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<pii> V(Q);
    for(auto &[t, v]: V) cin >> v >> t;

    sort(all(V));

    vector<int> sz(N), F(N, -1);
    auto dfs = [&](int v, int f, auto &&dfs) -> void {
        sz[v] = 1;

        for(auto u: adj[v]) {
            if(u == f || F[u] >= 0) continue;

            dfs(u, v, dfs);
            sz[v] += sz[u];
        }
    };

    auto find_centroid = [&](int v, int f, int n, auto &&find_centroid) -> int {
        for(auto u: adj[v]) {
            if(u == f || F[u] >= 0) continue;

            if(sz[u] > n/2) {
                return find_centroid(u, v, n, find_centroid);
            }
        }

        return v;
    };

    auto decompose = [&](int v, int f, auto &&decompose) -> void {
        dfs(v, -1, dfs);
        if(v) v = find_centroid(v, -1, sz[v], find_centroid);
        // if(v) to force 0 as centroid root

        F[v] = f;
        for(auto u: adj[v]) {
            if(F[u] >= 0) continue;

            decompose(u, v, decompose);
        }
    };

    decompose(0, N, decompose);

    infor("centroid:");
    for(auto x: F) {
        infor(" %d", x);
    }

    infof("");

    vector<int> tour, in(N), d(N);
    auto find_tour = [&](int v, int f, auto &&find_tour) -> void {
        in[v] = tour.size();

        tour.emplace_back(v);
        for(auto u: adj[v]) {
            if(u == f) continue;

            d[u] = 1 + d[v];
            tour.emplace_back(v);
            find_tour(u, v, find_tour);
        }
    };

    d[0] = 0;
    find_tour(0, -1, find_tour);

    vector tbl(LOG, vector<pii>(tour.size()));
    for(int i = 0; i < tour.size(); ++i) {
        tbl[0][i] = {d[tour[i]], tour[i]};
    }

    for(int lg = 0; lg + 1 < LOG; ++lg) {
        for(int i = 0; i + (1 << (lg + 1)) < tour.size(); ++i) {
            tbl[lg + 1][i] = min(tbl[lg][i], tbl[lg][i + (1 << lg)]);
        }
    }

    auto get_lca = [&](int u, int v) -> int {
        if(u == v) return u;

        int l = in[u], r = in[v];
        if(l > r) swap(l, r);

        int lg = 31 - __builtin_clz(r - l);

        return min(tbl[lg][l], tbl[lg][r - (1 << lg)]).se;
    };

    auto dist = [&](int u, int v) -> int {
        int lca = get_lca(u, v);

        /*
        infof("... - dist(%d, %d) -> %d [l = %d] [%d + %d - 2 * %d]",
                u, v, d[u] + d[v] - 2 * d[lca], lca, d[u], d[v], d[lca]);
        */

        return d[u] + d[v] - 2 * d[lca];
    };

    vector<MonotonicMap> dp(N); dp[0].push(0, 0);
    for(auto [t, v]: V) {
        infof("===== processing (%d, %d) =====", t, v);
        int mx = -1;
        for(int u = v; u < N; u = F[u]) {
            auto it = dp[u].m.upper_bound(t - dist(u, v));

            if(it == dp[u].m.begin()) continue;
            it = prev(it);

            mx = max(mx, it->se);
        }

        if(mx < 0) continue;

        mx += 1;

        infof("Found mx = %d", mx);

        for(int u = v; u < N; u = F[u]) {
            infof("... pushing %d: t + dist(u, v) = %d", u, t + dist(u, v));
            dp[u].push(t + dist(u, v), mx);
        }
    }

    for(int i = 0; i < N; ++i) {
        infof("======= dp[%d] =======", i);

        for(auto [t, k]: dp[i].m) {
            infof("... time %d -> k = %d", t, k);
        }
    }

    if(dp[0].m.empty()) {
        cout << 0 << lf;
    } else cout << prev(dp[0].m.end())->se << lf;
}
