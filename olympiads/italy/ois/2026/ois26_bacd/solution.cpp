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

int add(int a, int b) {
    int x = a + b;

    if(x >= MOD)
        return x - MOD;
    return x;
}

void chadd(int &a, int b) {
    a = add(a, b);
}

int mul(int a, int b) {
    return ((ll)a * b) % MOD;
}

void chmul(int &a, int b) {
    a = mul(a, b);
}

struct SegTree {
    SegTree(int N):
        N(N), H(31 - __builtin_clz(N)),
        st(2 * N), lz(2 * N), sz(2 * N, 1)
    {
        for(int i = N - 1; i > 0; i--)
            sz[i] = sz[i << 1] + sz[i << 1 | 1];
    }

    void apply(int v, int x) {
        chadd(lz[v], x);
        chadd(st[v], mul(x, sz[v]));
    }

    void push(int v) {
        apply(v << 1, lz[v]);
        apply(v << 1 | 1, lz[v]);

        lz[v] = 0;
    }

    void pull(int v) {
        sz[v] = sz[v << 1] + sz[v << 1 | 1];
        st[v] = add(st[v << 1], st[v << 1 | 1]);
    }

    void propagate(int v) {
        for(int h = H; h > 0; h--)
            push(v >> h);
    }

    void build(int v) {
        for(v >>= 1; v > 0; v >>= 1)
            push(v), pull(v);
    }

    void kill(int v) {
        v += N;

        propagate(v);

        st[v] = sz[v] = 0;

        build(v);
    }

    void range_add(int l, int r, int x) {
        l += N, r += N;
        int l0 = l, r0 = r - 1;

        propagate(l0), propagate(r0);

        for(; l < r; l >>= 1, r >>= 1) {
            if(l&1) apply(l++, x);
            if(r&1) apply(--r, x);
        }

        build(l0), build(r0);
    }

    int range_count(int l, int r) {
        if(l >= N) return 0;

        l += N, r += N;

        propagate(l), propagate(r - 1);

        int cnt = r - l;
        for(; l < r; l >>= 1, r >>= 1) {
            if(l&1) cnt -= sz[l++];
            if(r&1) cnt -= sz[--r];
        }

        return cnt;
    }

    int range_sum(int l, int r) {
        if(l >= N) return 0;

        l += N, r += N;

        propagate(l), propagate(r - 1);

        int sum = 0;
        for(; l < r; l >>= 1, r >>= 1) {
            if(l&1) chadd(sum, st[l++]);
            if(r&1) chadd(sum, st[--r]);
        }

        return sum;
    }

    int N, H;
    vector<int> st, lz, sz;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vector<int> P(N);
    for(auto &x: P) cin >> x, x--;

    int ans = 0;

    SegTree st(N);

    for(int i = N - 1; i >= 0; i--) {
        chadd(ans, st.range_sum(P[i] + 1, N));

        int cnt_d = st.range_count(P[i], N);

        st.kill(P[i]);

        st.range_add(0, P[i], cnt_d);
    }

    cout << ans << lf;
}
