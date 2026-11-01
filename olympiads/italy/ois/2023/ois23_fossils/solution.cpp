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

struct SegTree {
    SegTree(int N): N(N), st(2 * N), lz(N) {}

    void apply(int v, ll x) {
        infof("... apply(%d, %lld)", v, x);

        st[v] += x;

        if(v < N) lz[v] += x;
    }

    void push(int v) {
        if(v >= N) return;

        infof("push(%d) [%d]", v, lz[v]);

        apply(v << 1, lz[v]);
        apply(v << 1 | 1, lz[v]);

        lz[v] = 0;
    }

    void propagate(int v) {
        v += N;

        for(int h = LOG; h > 0; h--)
            push(v >> h);
    }

    ll query(int v) {
        propagate(v);

        infof("-------");
        infof("query(%d) -> %lld", v, st[v + N]);

        return st[v + N];
    }

    void update(int l, int r, ll x) {
        infof("-------");
        infof("update(%d, %d, %lld)", l, r, x);

        for(l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if(l&1) apply(l++, x);
            if(r&1) apply(--r, x);
        }
    }

    void print(void) {
        infor("lz:");
        for(auto x: lz)
            infor(" %lld", x);
        infof("");

        infor("st:");
        for(auto x: st)
            infor(" %lld", x);
        infof("");
    }

    int N;
    vector<ll> st, lz;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vector<vector<int>> adja(N);
    for(int i = 1; i < N; ++i) {
        int f; cin >> f; f--;

        adja[f].push_back(i);
    }

    int M; cin >> M;

    vector<vector<int>> adjb(M);
    for(int i = 1; i < M; ++i) {
        int f; cin >> f; f--;

        adjb[f].push_back(i);
    }

    int K; cin >> K;
    vector<vector<array<ll, 2>>> Ed(N);
    for(int i = 0; i < K; ++i) {
        ll u, v, w; cin >> u >> v >> w;
        u--, v--;

        Ed[u].push_back({v, w});
    }

    int Q; cin >> Q;
    vector<vector<array<int, 2>>> Qs(N);
    for(int i = 0; i < Q; ++i) {
        int u, v; cin >> u >> v;
        u--, v--;

        Qs[u].push_back({v, i});
    }

    vector<ll> ans(Q);

    vector<int> L(M), R(M);
    auto dfsb = [&](int v, auto &&dfsb) -> void {
        static int t = 0;

        L[v] = t++;

        for(auto u: adjb[v])
            dfsb(u, dfsb);

        R[v] = t;

        infof("%d: [%d, %d)", v, L[v], R[v]);
    };

    dfsb(0, dfsb);

    SegTree st(M);

    ll sum = 0;
    auto dfsa = [&](int v, auto &&dfsa) -> void {
        for(auto [u, w]: Ed[v])
            st.update(L[u], R[u], w);

        for(auto [u, i]: Qs[v]) {
            infof("===============");
            infof("Query: %d -- %d [%d]", v, u, i);

            st.print();
            ans[i] = st.query(L[u]);
            st.print();

            infof("===============");
        }

        for(auto u: adja[v])
            dfsa(u, dfsa);

        for(auto [u, w]: Ed[v])
            st.update(L[u], R[u], -w);
    };

    dfsa(0, dfsa);

    for(auto x: ans)
        cout << x << lf;
}
