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

mt19937 timmy_loves_gambling(73);

struct Node {
    Node(void): x(0), l(0), r(0) {}
    Node(int x): x(x), l(0), r(0) {}
    Node(int x, int l, int r): x(x), l(l), r(r) {}

    int x;
    int l, r;
};

vec<Node> T(1);

template<typename... Args>
int make_node(Args... args) {
    T.emplace_back(args...);
    return T.size() - 1;
}

int increment(int n, int l, int r, int q) {
    if(l > q || r <= q) return n;

    if(r - l <= 1) {
        return make_node(T[n].x + 1);
    }

    int m = (l + r) / 2;
    int nl = increment(T[n].l, l, m, q);
    int nr = increment(T[n].r, m, r, q);

    return make_node(T[nl].x + T[nr].x, nl, nr);
}

int get_kth_max(int u, int v, int lca, int lcp, int l, int r, int k) {
    if(r - l <= 1) return l;

    int m = (l + r) / 2;
    int szr = T[T[u].r].x + T[T[v].r].x - T[T[lca].r].x - T[T[lcp].r].x;

    if(szr > k) {
        return get_kth_max(T[u].r, T[v].r, T[lca].r, T[lcp].r, m, r, k);
    } else {
        return get_kth_max(T[u].l, T[v].l, T[lca].l, T[lcp].l, l, m, k - szr);
    }
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vec<int> V(N + 1);
    for(int i = 1; i <= N; ++i) {
        cin >> V[i];
    }

    vec<int> p(N + 1);
    vec<vec<int>> adj(N + 1);
    for(int i = 2; i <= N; ++i) {
        cin >> p[i];
        adj[p[i]].emplace_back(i);
    }

    vec<int> tour; tour.reserve(2 * N - 1);
    vec<int> d(N + 1), t(N + 1), in(N + 1);

    auto dfs = [&](int u, auto &&dfs) -> void {
        t[u] = increment(t[p[u]], 0, N + 1, V[u]);
        in[u] = tour.size();

        for(auto v: adj[u]) {
            d[v] = 1 + d[u];
            tour.emplace_back(u);

            dfs(v, dfs);
        }

        tour.emplace_back(u);
    };

    dfs(1, dfs);

    const int M = tour.size();
    constexpr int LOG = 20;

    vector tbl(LOG, vec<pii>(M));
    for(int i = 0; i < M; ++i) {
        tbl[0][i] = {d[tour[i]], tour[i]};
    }

    for(int lg = 0; lg < LOG - 1; ++lg) {
        int pow = 1 << lg;
        for(int i = 0; i + 2 * pow < M; ++i) {
            tbl[lg + 1][i] = min(tbl[lg][i], tbl[lg][i + pow]);
        }
    }

    auto get_lca = [&](int u, int v) -> int {
        if(in[u] > in[v]) swap(u, v);

        int l = in[u], r = in[v] + 1;

        int lg = 31 - __builtin_clz(r - l);
        int pow = 1 << lg;

        return min(tbl[lg][l], tbl[lg][r - pow]).se;
    };

    int Q; cin >> Q;

    for(int q = 0; q < Q; ++q) {
        int u, v, k; cin >> u >> v >> k;
        k -= 1;

        int lca = get_lca(u, v);
        cout << get_kth_max(t[u], t[v], t[lca], t[p[lca]], 0, N + 1, k) << lf;
    }
}
