#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
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

struct SegTree {
    SegTree(int N, const vector<int> &V): N(N), T(2 * N) {
        for(int i = 0; i < N; ++i) {
            T[i + N] = V[i];
        }

        for(int i = N - 1; i > 0; i--) {
            pull(i);
        }
    }

    inline void pull(int v) {
        T[v] = T[v << 1] + T[v << 1 | 1];
    }

    void point_set(int v, int x) {
        T[v += N] = x;

        for(v >>= 1; v > 0; v >>= 1) {
            pull(v);
        }
    }

    int range_sum(int l, int r) {
        int sum = 0;

        for(l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if(l&1) sum += T[l++];
            if(r&1) sum += T[--r];
        }

        return sum;
    }

    int N;
    vector<int> T;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vector<int> dg(N);
    vector<vector<int>> adj(N), radj(N);
    for(int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;
        u -= 1, v -= 1;

        dg[max(u, v)] += 1;

        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    SegTree st(N, dg);

    set<int> s;
    s.emplace(-1);
    s.emplace(N);

    vector<int> idx(N); iota(all(idx), 0);
    vector<int> pos(N); iota(all(pos), 0);

    int sum = 0;
    for(int i = 1; i < N; ++i) {
        if(sum == i - 1 && dg[i] == 0) {
            s.emplace(i);
        }

        sum += dg[i];
    }

    infor("s:");
    for(auto x: s) {
        infor(" %d", x);
    }

    infof("");

    for(int i = 0; i < N; ++i) {
        infor("%d: dg[i] = %d |", i, st.T[i + N]);
        for(auto u: adj[pos[i]]) {
            infor(" %d", idx[u]);
        }

        infof("");
    }

    auto update = [&](int a, int b) -> void {
        infof("======= update(%d, %d) =======", a, b);

        infof("idx[a] = %d | idx[b] = %d", idx[a], idx[b]);

        bool is_adj = 0;
        dg[idx[a]] = dg[idx[b]] = 0;

        infof("a: {");
        for(auto u: adj[a]) {
            if(u == b) {
                is_adj = 1;
                continue;
            }

            infof("  u = %d | idx[u] = %d", u, idx[u]);

            if((idx[u] < idx[a]) == (idx[u] < idx[b])) continue;

            if(idx[u] < idx[a]) {
                infof("  ... b < u < a");

                dg[idx[u]] += 1;
            } else {
                infof("  ... a < u < b");

                dg[idx[u]] -= 1;
            }
        }
        infof("}\n");

        infof("b: {");
        for(auto u: adj[b]) {
            if(u == a) continue;
            infof("  u = %d | idx[u] = %d", u, idx[u]);

            if((idx[u] < idx[a]) == (idx[u] < idx[b])) continue;

            if(idx[u] < idx[b]) {
                infof("  ... a < u < b");

                dg[idx[u]] += 1;
            } else {
                infof("  ... b < u < a");

                dg[idx[u]] -= 1;
            }
        }
        infof("}\n");

        swap(a, b);
        swap(idx[a], idx[b]);
        swap(pos[idx[a]], pos[idx[b]]);

        for(auto u: adj[a]) dg[idx[a]] += idx[a] > idx[u];
        for(auto u: adj[b]) dg[idx[b]] += idx[b] > idx[u];

        st.point_set(idx[a], dg[idx[a]]);
        st.point_set(idx[b], dg[idx[b]]);

        for(auto u: adj[a]) st.point_set(idx[u], dg[idx[u]]);
        for(auto u: adj[b]) st.point_set(idx[u], dg[idx[u]]);

        auto push = [&](int v) -> void {
            for(const int v0 = v; v < v0 + 2; ++v) {
                if(v == 0 || v >= N) continue;

                if(idx[v] == 0) return;

                int x = st.range_sum(0, idx[v]);

                infof("... push(%d): x = %d | dg = %d | idx = %d",
                       v, x, dg[idx[v]], idx[v]);

                if(x == idx[v] - 1 && dg[idx[v]] == 0) {
                    s.emplace(idx[v]);
                } else s.erase(idx[v]);
            }
        };

        push(a);
        push(b);

        for(auto u: adj[a]) push(u);
        for(auto u: adj[b]) push(u);

        infor("... s:");
        for(auto x: s) {
            infor(" %d", x);
        }

        infof("");

        for(int i = 0; i < N; ++i) {
            infor("%d: pos[i] = %d | dg[i] = %2d |", i, pos[i], dg[i]);
            for(auto u: adj[pos[i]]) {
                infor(" %d", idx[u]);
            }

            infof("");
        }
    };

    auto query = [&](int K) -> int {
        infof("======= query(%d) =======", K);

        auto n = s.upper_bound(K);
        auto p = prev(n);

        auto check = [&](int v) -> bool {
            infof("... check(%d)", v);

            if(v < 0) return 0;

            int sum = st.range_sum(0, v + 1);

            infof("... - sum = %d", sum);

            return sum == v;
        };

        int l = *p, r = *n;
        infof("l = %d | r = %d", l, r);

        while(r - l > 1) {
            int m = (l + r) / 2;

            if(check(m)) {
                r = m;
            } else l = m;
        }

        infof("Found l = %d", l);

        return max(l + 1, K);
    };

    int Q; cin >> Q;
    while(Q--) {
        int t; cin >> t;

        if(t == 1) {
            int u, v; cin >> u >> v;

            update(pos[u - 1], pos[v - 1]);
        } else {
            int K; cin >> K;

            cout << query(K - 1) + 1 << lf;
        }
    }
}
