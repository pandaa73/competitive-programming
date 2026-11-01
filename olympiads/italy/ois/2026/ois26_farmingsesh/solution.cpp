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
constexpr int MAXN = 5e5+7;

struct SegTree {
    struct Node {
        Node(void): l(0), r(0), sz(0), sum(0) {}

        int l, r;

        int sz;
        ll sum;
    };

    SegTree(int N): N(N) {
        T.reserve(MAXN * LOG * 8);
    }

    inline int make_node() {
        T.emplace_back();
        return T.size() - 1;
    }

    inline int pull(int v) {
        int l = T[v].l;
        int r = T[v].r;

        T[v].sz = T[l].sz + T[r].sz;
        T[v].sum = T[l].sum + T[r].sum;

        return v;
    }

    int increment(int v, int l, int r, int q, ll x) {
        if(q < l || q >= r) return v;

        int n = make_node();
        if(r - l == 1) {
            T[n].sz = T[v].sz + 1;
            T[n].sum = T[v].sum + x;

            return n;
        }

        int m = (l + r) / 2;
        T[n].l = increment(T[v].l, l, m, q, x);
        T[n].r = increment(T[v].r, m, r, q, x);

        return pull(n);
    }

    static ll sum_max_k(int vl, int vr, int nl, int nr, int l, int r, int k) {
        if(r - l == 1) {
            int sz = T[vr].sz + T[nr].sz - T[vl].sz - T[nl].sz;
            ll sum = T[vr].sum + T[nr].sum - T[vl].sum - T[nl].sum;

            return sz ? k * (sum / sz) : 0;
        }

        int sz = T[T[vr].r].sz + T[T[nr].r].sz - T[T[vl].r].sz - T[T[nl].r].sz;

        int m = (l + r) / 2;

        if(sz > k) {
            return sum_max_k(T[vl].r, T[vr].r, T[nl].r, T[nr].r, m, r, k);
        }

        k -= sz;

        ll sum = T[T[vr].r].sum + T[T[nr].r].sum - T[T[vl].r].sum
            - T[T[nl].r].sum;

        if(k == 0) return sum;

        return sum + sum_max_k(T[vl].l, T[vr].l, T[nl].l, T[nr].l, l, m, k);
    }

    int N;
    static vector<Node> T;
};

vector<SegTree::Node> SegTree::T(1);

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    SegTree::T.emplace_back();

    int N, M, Q; cin >> N >> M >> Q;

    vector<int> A(N), B(M);
    for(auto &x: A) cin >> x;
    for(auto &x: B) cin >> x;

    vector<int> V = A; V.reserve(N + M);
    for(auto x: B) V.emplace_back(x);

    sort(all(V));
    V.resize(unique(all(V)) - V.begin());

    const int K = V.size();

    SegTree st_A(K), st_B(K);

    vector<int> root_A(N + 1);
    for(int i = 0; i < N; ++i) {
        int j = lower_bound(all(V), A[i]) - V.begin();
        root_A[i + 1] = st_A.increment(root_A[i], 0, K, j, A[i]);
    }

    vector<int> root_B(M + 1);
    for(int i = 0; i < M; ++i) {
        int j = lower_bound(all(V), B[i]) - V.begin();
        root_B[i + 1] = st_B.increment(root_B[i], 0, K, j, B[i]);
    }

    for(int q = 0; q < Q; ++q) {
        int vl, vr; cin >> vl >> vr; vr += 1;
        int nl, nr; cin >> nl >> nr; nr += 1;

        ll x = SegTree::sum_max_k(
            root_A[vl], root_A[vr],
            root_B[nl], root_B[nr],
            0, K,
            vr - vl
        );

        cout << x << lf;
    }
}
