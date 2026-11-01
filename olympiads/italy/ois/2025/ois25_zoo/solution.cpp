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

template<typename... Args>
using vec = vector<Args...>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

mt19937 timmy_loves_gambling(73);

constexpr int INF = 1e9;

struct SegTree {
    SegTree(int N): N(N), T(2 * N) {}

    void increment(int v) {
        T[v += N] += 1;

        for(v >>= 1; v > 0; v >>= 1) {
            T[v] = T[v << 1] + T[v << 1 | 1];
        }
    }

    int range_sum(int l, int r) {
        int s = 0;

        for(l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if(l&1) s += T[l++];
            if(r&1) s += T[--r];
        }

        return s;
    }

    int N;
    vec<int> T;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M; cin >> N >> M;

    const int S = 0;
    const int T = N - 1;

    vec<vec<int>> adj(N);
    for(int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;

        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    auto bfs = [&](int s, vec<int> &ds) -> void {
        ds.assign(N, INF);

        queue<int> q; q.emplace(s); ds[s] = 0;
        while(!q.empty()) {
            auto v = q.front(); q.pop();

            for(auto u: adj[v]) {
                if(ds[u] < INF) continue;

                ds[u] = ds[v] + 1;
                q.emplace(u);
            }
        }
    };

    vec<int> ds, dt;
    bfs(S, ds), bfs(T, dt);

    vec<int> cnt(N + 1);
    for(int i = 0; i < N; ++i) {
        cnt[dt[i]] += 1;
    }

    for(int i = N - 2; i >= 0; i--) {
        cnt[i] += cnt[i + 1];
    }

    infof(" ds: {}", ds);
    infof(" dt: {}", dt);
    infof("cnt: {}", cnt);

    vec<int> P(N); iota(all(P), 0);
    sort(all(P), [&](int i, int j) -> bool {
        return ds[i] > ds[j];
    });

    vec<int> Q(N);
    for(int i = 0; i < N; ++i) {
        Q[P[i]] = i;
    }

    SegTree st(N);

    ll ans = 0;
    for(auto u: P) {
        ans += st.range_sum(max(0, ds[T] - ds[u] - 1), N);
        st.increment(dt[u]);

        for(auto v: adj[u]) {
            if(Q[v] > Q[u]) continue;

            ans -= ds[u] + 1 + dt[v] >= ds[T];
        }

        infof("{}: ans = {}", u, ans);
    }

    cout << ans << lf;
}
