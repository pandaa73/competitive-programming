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

using tiii = tuple<int, int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

constexpr int ROOT = 1024;
constexpr ll INF = 1e18;

struct DSU {
    DSU(int N): p(N, -1) {}

    int find(int n) {
        return p[n] < 0 ? n : p[n] = find(p[n]);
    }

    bool join(int &u, int &v) {
        u = find(u);
        v = find(v);

        if(u == v) return false;

        if(p[u] > p[v]) {
            swap(u, v);
        }

        p[u] += p[v];
        p[v] = u;

        return true;
    }

    vec<int> p;
};

struct DSUTree {
    // dsu + get valid ordering

    DSUTree(int N): N(N), dsu(N), t(N) {
        iota(all(t), 0);

        l.reserve(N);
        r.reserve(N);
    }

    void join(int u, int v) {
        if(!dsu.join(u, v)) return;

        l.emplace_back(t[u]);
        r.emplace_back(t[v]);

        t[u] = N + l.size() - 1;
    }

    void visit(int n, vec<int> &ord) {
        if(n < N) {
            ord.emplace_back(n);
        } else {
            visit(l[n - N], ord);
            visit(r[n - N], ord);
        }
    }

    int N;
    DSU dsu;
    vec<int> t, l, r;
};

struct DSURange {
    // dsu + get valid ranges

    DSURange(int N, const vec<vec<int>> &ord): N(N), dsu(N), rg(N) {
        for(int b = 0; b < ord.size(); ++b) {
            for(int l = 0; l < ord[b].size(); ++l) {
                rg[ord[b][l]].emplace_back(b, l, l + 1);
            }
        }
    }

    void join(int u, int v) {
        if(!dsu.join(u, v)) return;

        vec<tiii> nr;
        int i = 0, j = 0;
        for(; i < rg[u].size() && j < rg[v].size();) {
            auto [bu, lu, ru] = rg[u][i];
            auto [bv, lv, rv] = rg[v][j];

            if(bu < bv) {
                nr.emplace_back(rg[u][i++]);
            } else if(bv < bu) {
                nr.emplace_back(rg[v][j++]);
            } else {
                nr.emplace_back(bu, min(lu, lv), max(ru, rv));
                i += 1, j += 1;
            }
        }

        for(; i < rg[u].size(); ++i) {
            nr.emplace_back(rg[u][i]);
        }

        for(; j < rg[v].size(); ++j) {
            nr.emplace_back(rg[v][j]);
        }

        swap(rg[u], nr);
    }

    vec<tiii> get_range(int u) {
        return rg[dsu.find(u)];
    }

    int N;
    DSU dsu;
    vec<vec<tiii>> rg;
};

struct SegTree {
    // range add, point query / tree min
    // no need to propagate lazy!

    struct Node {
        Node(void): x(0LL), z(0LL) {}

        ll x, z;
    };

    SegTree(void) {}
    SegTree(int N): N(N), T(2 * N) {}

    void apply(int n, ll x) {
        T[n].x += x;
        T[n].z += x;
    }

    void pull(int n) {
        if(n >= N) return;

        T[n].x = T[n].z + min(T[n << 1].x, T[n << 1 | 1].x);
    }

    void build(int n) {
        for(; n > 0; n >>= 1) {
            pull(n);
        }
    }

    void flatten(void) {
        for(int n = 1; n < N; ++n) {
            apply(n << 1, T[n].z);
            apply(n << 1 | 1, T[n].z);
            T[n].z = 0;
        }
    }

    ll tree_min(void) {
        return T[1].x;
    }

    ll get(int n) {
        return T[N + n].x;
    }

    void range_add(int l, int r, ll x) {
        l += N, r += N;
        const int l0 = l, r0 = r - 1;

        for(; l < r; l >>= 1, r >>= 1) {
            if(l&1) apply(l++, x);
            if(r&1) apply(--r, x);
        }

        build(l0), build(r0);
    }

    int N;
    vec<Node> T;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M, Q; cin >> N >> M >> Q;

    vec<tiii> ed(M);
    for(auto &[w, u, v]: ed) {
        cin >> u >> v >> w;
    }

    sort(all(ed));

    vec<vec<int>> Qs(Q);
    for(int qi = 0; qi < Q; ++qi) {
        int t; cin >> t;
        Qs[qi].resize(4 - t);
        for(auto &x: Qs[qi]) {
            cin >> x;
        }
    }

    vec<int> qord(Q);
    iota(all(qord), 0);
    sort(all(qord), [&](int i, int j) -> bool {
        return Qs[i][1] < Qs[j][1];
    });

    const int BLOCKS = (N + ROOT - 1) / ROOT;

    DSUTree dt(N);
    for(auto [w, u, v]: ed) {
        dt.join(u, v);
    }

    vec<int> tord;
    vec<vec<int>> ord(BLOCKS);
    for(int n = 0; n < N; ++n) {
        if(dt.dsu.p[n] >= 0) continue;
        dt.visit(dt.t[n], tord);
    }

    for(auto n: tord) {
        ord[n / ROOT].emplace_back(n);
    }

    vec<int> dro(N);
    for(int b = 0; b < BLOCKS; ++b) {
        for(int i = 0; i < ord[b].size(); ++i) {
            dro[ord[b][i]] = i;
        }
    }

    DSURange dr(N, ord);
    vec<vec<tiii>> rg(Q);
    for(int qii = 0, e = 0; qii < Q; ++qii) {
        int qi = qord[qii];
        if(Qs[qi].size() == 2) continue;

        int n = Qs[qi][0], k = Qs[qi][1];

        for(; e < M; ++e) {
            auto [w, u, v] = ed[e];
            if(w > k) break;

            dr.join(u, v);
        }

        rg[qi] = dr.get_range(n);
    }

    vec<SegTree> st(BLOCKS, ROOT);
    if(N % ROOT) st.back() = SegTree(N % ROOT);

    for(int qi = 0; qi < Q; ++qi) {
        if(Qs[qi].size() == 3) {
            int x = Qs[qi][2];

            for(auto [b, l, r]: rg[qi]) {
                st[b].range_add(l, r, x);
            }
        } else {
            int l = Qs[qi][0];
            int r = Qs[qi][1] + 1;

            ll x = INF;

            if(l / ROOT == r / ROOT) {
                int b = l / ROOT;

                st[b].flatten();
                for(; l < r; ++l) {
                    x = min(x, st[b].get(dro[l]));
                }
            } else {
                int bl = (l + ROOT - 1) / ROOT;
                int br = r / ROOT;

                for(int b = bl; b < br; ++b) {
                    x = min(x, st[b].tree_min());
                }

                if(bl > 0) {
                    st[bl - 1].flatten();
                    for(int n = l; n < bl * ROOT; ++n) {
                        x = min(x, st[bl - 1].get(dro[n]));
                    }
                }

                if(br < BLOCKS) {
                    st[br].flatten();
                    for(int n = br * ROOT; n < r; ++n) {
                        x = min(x, st[br].get(dro[n]));
                    }
                }
            }

            cout << x << lf;
        }
    }
}
