#include <bits/stdc++.h>
using namespace std;

#include <cassert>

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

#endif /* DEBUG */

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M, K; cin >> N >> M >> K;

    vec<ll> S(M), T(M);
    vec<int> U(M), V(M);
    for(int e = 0; e < M; ++e) {
        cin >> U[e] >> S[e] >> V[e] >> T[e];
    }

    int L; cin >> L;

    vec<pii> C(L);
    for(auto &[u, v]: C) {
        cin >> u >> v;
    }

    vec<vec<pll>> F(N);
    for(int e = 0; e < M; ++e) {
        F[U[e]].emplace_back(S[e], e);
        F[V[e]].emplace_back(T[e], e);
    }

    vec<vec<int>> G(6 * M), Gt(6 * M);
    auto add_edge = [&](int u, int v) -> void {
        G[u].emplace_back(v);
        Gt[v].emplace_back(u);
    };

    auto add_clause = [&](int u, int v) -> void {
        add_edge(u, v);
        add_edge(v ^ 1, u ^ 1);
    };

    vec<vec<int>> st(N);
    for(int t = 0; t < N; ++t) {
        sort(all(F[t]));
        const int K = F[t].size();
        st[t].resize(2 * K);

        for(int n = 0; n < K; ++n) {
            st[t][n + K] = F[t][n].se << 1;
        }

        static int x = 2 * M;
        for(int n = K - 1; n > 0; n--) {
            st[t][n] = x;
            x += 2;

            add_clause(st[t][n] ^ 1, st[t][n << 1] ^ 1);
            add_clause(st[t][n] ^ 1, st[t][n << 1 | 1] ^ 1);
        }
    }

    auto add_range = [&](int n, int v, int l, int r, bool s) -> void {
        const int N = F[v].size();

        for(l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if(l&1) add_clause(n, st[v][l++] ^ s);
            if(r&1) add_clause(n, st[v][--r] ^ s);
        }
    };

    for(int e = 0; e < M; ++e) {
        int u = U[e], v = V[e];
        ll s = S[e], t = T[e];

        int lu = upper_bound(all(F[u]), (pll){    s, e}) - F[u].begin();
        int ru = upper_bound(all(F[u]), (pll){s + K, M}) - F[u].begin();

        int lv = upper_bound(all(F[v]), (pll){    t, e}) - F[v].begin();
        int rv = upper_bound(all(F[v]), (pll){t + K, M}) - F[v].begin();

        add_range(e << 1, u, lu, ru, true);
        add_range(e << 1, v, lv, rv, true);
    }

    for(auto [u, v]: C) {
        add_clause(u << 1 | 1, v << 1);
    }

    vec<bool> vis(6 * M, false);
    auto dfs = [&](int u, const vec<vec<int>> &G, vec<int> &ord, auto &&dfs)
            -> void {
        vis[u] = true;

        for(auto v: G[u]) {
            if(!vis[v]) {
                dfs(v, G, ord, dfs);
            }
        }

        ord.emplace_back(u);
    };

    vec<int> ord; ord.reserve(6 * M);
    for(int e = 0; e < 6 * M; ++e) {
        if(!vis[e]) {
            dfs(e, G, ord, dfs);
        }
    }

    vec<int> scc(6 * M);

    reverse(all(ord));
    fill(all(vis), false);
    for(auto u: ord) {
        if(vis[u]) continue;

        vec<int> nds;
        dfs(u, Gt, nds, dfs);

        static int c = 0;
        for(auto v: nds) {
            scc[v] = c;
        }

        c += 1;
    }

    bool ok = true;
    vec<bool> ans(M);

    for(int e = 0; e < M; ++e) {
        int a = e << 1, b = e << 1 | 1;
        ok &= scc[a] != scc[b];
        ans[e] = scc[a] > scc[b];
    }

    if(ok) {
        cout << "YES" << lf;
        for(auto state: ans) {
            cout << state << " ";
        }

        cout << lf;
    } else {
        cout << "NO" << lf;
    }
}
