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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

constexpr int add(int a, int b) {
    return (a + b) % MOD;
}

constexpr void chadd(int &a, int b) {
    a = add(a, b);
}

constexpr int mul(ll a, ll b) {
    return (a * b) % MOD;
}

constexpr void chmul(int &a, int b) {
    a = mul(a, b);
}

constexpr int fexp(int b, int e) {
     int ans = 1;

     while(e > 0) {
         if(e&1) chmul(ans, b);

         e >>= 1;
         chmul(b, b);
     }

     return ans;
}

constexpr int INV2 = fexp(2, MOD - 2);

struct Node {
    Node(void): lz(-1), sum(-1) {}
    Node(int x):
        lz(-1), sz(1), sum(x), prod(x + 1),
        ans(x), cnt(1), ansl(x), cntl(1), ansr(x), cntr(1)
    {}

    void print(int i = -1) {
        if(i >= 0) {
            infof("===== Node %3d =====", i);
            infof("children: l = %d | r = %d", i << 1, i << 1 | 1);
        }

        infof("   lz = %d", lz);
        infof("   sz = %d", sz);
        infof("  sum = %d | prod = %d", sum,  prod);
        infof("  ans = %d |  cnt = %d", ans,  cnt);
        infof(" ansl = %d | cntl = %d", ansl, cntl);
        infof(" ansr = %d | cntr = %d", ansr, cntr);
    }

    int lz;
    int sz;

    int sum;
    int prod;

    int ans, cnt;
    int ansl, cntl;
    int ansr, cntr;
};

Node merge(Node l, Node r) {
    if(l.sum < 0) return r;
    if(r.sum < 0) return l;

    // I love iterative segment trees :)
    //assert(l.r == r.l);

    Node ans;

    chadd(l.ans, mul(l.ansl, r.sz)); // r.r - l.r
    chadd(r.ans, mul(r.ansr, l.sz)); // r.l - l.l

    chadd(l.cnt, mul(l.cntl, r.sz));
    chadd(r.cnt, mul(r.cntl, l.sz));

    chadd(l.ansr, mul(l.sum, r.sz)); // r.r - l.r
    chadd(r.ansl, mul(r.sum, l.sz)); // r.l - l.l

    chadd(l.cntr, mul(l.sz, r.sz)); // l.r - l.l | r.r - l.r
    chadd(r.cntl, mul(r.sz, l.sz)); // r.r - r.l | r.l - l.l

    ans.sz = l.sz + r.sz;

    ans.sum  = add(l.sum, r.sum);
    ans.prod = mul(l.prod, r.prod);

    ans.ans  = add(l.ans,  r.ans);
    ans.cnt  = add(l.cnt,  r.cnt);
    ans.ansl = add(l.ansl, r.ansl);
    ans.cntl = add(l.cntl, r.cntl);
    ans.ansr = add(l.ansr, r.ansr);
    ans.cntr = add(l.cntr, r.cntr);

    return ans;
}

struct SegTree {
    SegTree(int N, const vector<int> &V): N(N), st(2 * N) {
        infor("info: Building SegTree...");

        H = 31 - __builtin_clz(N);

        for(int i = 0; i < N; ++i)
            st[i + N] = Node(V[i]);

        for(int i = N - 1; i > 0; i--)
            st[i] = merge(st[i << 1], st[i << 1 | 1]);

        infof(" done");
    }

    void apply(int v, int x) {
        infof("... apply(%d, %d)", v, x);

        if(v >= N) return (void)(st[v] = Node(x));

        Node &n = st[v];

        n.lz = x;

        st[v].sum  = mul(x, n.sz);      // n.r - n.l
        st[v].prod = fexp(x + 1, n.sz); // n.r - n.l

        n.ans  = mul(x, n.cnt);
        n.ansl = mul(x, n.cntl);
        n.ansr = mul(x, n.cntr);
    }

    void push(int v) {
        if(st[v].lz < 0) return;

        apply(v << 1, st[v].lz);
        apply(v << 1 | 1, st[v].lz);

        st[v].lz = -1;
    }

    void build(int v) {
        for(v >>= 1; v > 0; v >>= 1) {
            push(v);
            st[v] = merge(st[v << 1], st[v << 1 | 1]);
        }
    }

    void propagate(int v) {
        for(int h = H; h >= 0; h--)
            push(v >> h);
    }

    void update(int l, int r, int x) {
        l += N, r += N;
        int l0 = l, r0 = r - 1;

        propagate(l0), propagate(r0);

        for(; l < r; l >>= 1, r >>= 1) {
            if(l&1) apply(l++, x);
            if(r&1) apply(--r, x);
        }

        build(l0), build(r0);
    }

    int query(int l, int r) {
        l += N, r += N;
        int l0 = l, r0 = r - 1;

        propagate(l0), propagate(r0);

        Node L, R;
        for(; l < r; l >>= 1, r >>= 1) {
            if(l&1) L = merge(L, st[l++]);
            if(r&1) R = merge(st[--r], R);
        }

        Node ans = merge(L, R);

        infof("... st.query(%d, %d):", l0, r0 + 1);
        ans.print();

        return mul(ans.ans, mul(ans.prod, INV2));
    }

    void print(void) {
        infof("======= SegTree =======");

        for(int i = 1; i < 2 * N; ++i)
            st[i].print(i);

        infof("======= eerTgeS =======");
    }

    int N, H;
    vector<Node> st;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, Q; cin >> N >> Q;

    vector<int> V(N);
    for(auto &x: V) cin >> x;

    SegTree st(N, V);

    //st.print();

    for(int q = 0; q < Q; ++q) {
        infof("======= Query %d =======", q);

        int t, l, r; cin >> t >> l >> r;
        r++;

        infof("t = %d: [%d, %d)", t, l, r);

        if(t == 1) {
            int x; cin >> x;

            infof("... x = %d", x);

            st.update(l, r, x);
            st.print();
        } else cout << st.query(l, r) << lf;
    }

    st.print();
}
