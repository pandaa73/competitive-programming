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

constexpr int ROOT = 18; // root_3(N / log(N)) ~= 18

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vector<vector<int>> adj(N);
    for(int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;

        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> d(N, -1), in(N), tour; tour.reserve(2 * N - 1);
    auto dfs = [&](int v, auto &&dfs) -> void {
        in[v] = tour.size();

        for(auto u: adj[v]) {
            if(d[u] >= 0) continue;

            d[u] = 1 + d[v];
            tour.emplace_back(v);

            dfs(u, dfs);
        }

        tour.emplace_back(v);
    };

    d[0] = 0;
    dfs(0, dfs);

    vector tbl(LOG, vector<pii>(tour.size()));
    for(int i = 0; i < tour.size(); ++i) {
        tbl[0][i] = {d[tour[i]], tour[i]};
    }

    for(int lg = 0; lg < LOG - 1; ++lg) {
        for(int i = 0; i + (1 << (lg + 1)) < tour.size(); ++i) {
            tbl[lg + 1][i] = min(tbl[lg][i], tbl[lg][i + (1 << lg)]);
        }
    }

    auto get_lca = [&](int u, int v) -> int {
        if(in[u] > in[v]) swap(u, v);
        int l = in[u], r = in[v];

        int lg = 31 - __builtin_clz(r - l);

        return min(tbl[lg][l], tbl[lg][r - (1 << lg)]).se;
    };

    auto get_dist = [&](int u, int v) -> int {
        int lca = get_lca(u, v);

        return d[u] + d[v] - 2 * d[lca];
    };

    infof("d: {}", d);
    infof("tour: {}", tour);
    infof("tbl: {}", tbl);

    vector<int> F(N, -1), sz(N);
    auto calc_sz = [&](int v, int f, auto &&calc_sz) -> void {
        sz[v] = 1;
        for(auto u: adj[v]) {
            if(u == f || F[u] >= 0) continue;

            calc_sz(u, v, calc_sz);

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

    vector<vector<int>> T(N), adj2(N);
    auto decompose = [&](int v, int f, auto &&decompose) -> int {
        calc_sz(v, -1, calc_sz);
        v = find_centroid(v, -1, sz[v], find_centroid);

        F[v] = f;
        T[v].emplace_back(v);
        for(auto u: adj[v]) {
            if(F[u] >= 0) continue;

            u = decompose(u, v, decompose);

            adj2[v].emplace_back(u);
            for(auto x: T[u]) {
                T[v].emplace_back(x);
            }
        }

        return v;
    };

    int root = decompose(0, N, decompose);

    infof("centroid_F: {}", F);

    ll ans = 0;

    infof("===== count_small_k =====");
    vector<int> cnt(2 * N), val(N);
    for(int k = 1; k < ROOT; ++k) {
        infof("--- Counting k = {} ---", k);

        for(int v = 0; v < N; ++v) {
            infof("----- v = {} -----", v);
            infof("T[v] = {}", T[v]);

            val[v] = N + min(N - 1, k * v);
            infof("val[v] = {}", val[v]);

            cnt[val[v]] = 1;
            for(auto u: adj2[v]) {
                infof("- visiting T[{}]", u);
                for(auto t: T[u]) {
                    val[t] = N + min(N - 1, k * t - get_dist(t, v));
                    infof("... {}: val[t] = {}", t, val[t]);

                    ans += cnt[2 * N - val[t]];
                }

                for(auto t: T[u]) cnt[val[t]] += 1;
            }

            for(auto u: T[v]) cnt[val[u]] = 0;
        }

        infof("ans = {}", ans);
    }

    infof("===== count_large_k =====");
    for(int s = 1; s < N/ROOT; ++s) {
        infof("--- Counting s = {} ---", s);
        for(int u = 0; u < (s + 1)/2; ++u) {
            int v = s - u;

            int dist = get_dist(u, v);

            int q = dist / s;
            int r = dist % s;

            if(r != 0) continue;
            if(q >= ROOT) ans += 1;
        }
    }

    cout << ans << lf;

    infof("");
    infof("NOTE!!! LOG = {} | ROOT = {}", LOG, ROOT);
    infof("NOTE!!! LOG = {} | ROOT = {}", LOG, ROOT);
    infof("NOTE!!! LOG = {} | ROOT = {}", LOG, ROOT);
    infof("NOTE!!! LOG = {} | ROOT = {}", LOG, ROOT);
    infof("NOTE!!! LOG = {} | ROOT = {}", LOG, ROOT);
}
