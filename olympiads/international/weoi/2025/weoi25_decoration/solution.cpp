#pragma GCC target("avx2,lzcnt")

#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infos(str) do { fprintf(stderr, str"\n"); } while(0)
#define infor(str, ...) do { fprintf(stderr, str, __VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", __VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infos
#undef infor
#undef infof

#define infos(str)
#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

constexpr short LOG = 10;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

struct SparseTable {
    SparseTable(void): built(0) {}
    SparseTable(short N, short top, const vector<array<short, 2>> &V):
            built(1), top(top),
            N(N), tbl(LOG, vector<array<short, 2>>(N, {SHRT_MAX, 0})) {
        tbl.shrink_to_fit();
        for(short i = 0; i < N; ++i)
            tbl[0][i] = V[i];

        short sz = 1;
        for(short lg = 1; lg < LOG; ++lg) {
            if(1 << lg > N) break;

            sz++;

            for(short i = 0; i + (1 << lg) <= N; ++i) {
                short j = i + (1 << (lg - 1));

                tbl[lg][i][0] = min(tbl[lg - 1][i][0], tbl[lg - 1][j][0]);
                tbl[lg][i][1] = max(tbl[lg - 1][i][1], tbl[lg - 1][j][1]);
            }
        }

        tbl.resize(sz);
        tbl.shrink_to_fit();
    }

    array<short, 2> range_query(short l, short r) {
        assert(built);

        short lg = 31 - __builtin_clz(r - l);
        lg = min(lg, (short)(LOG - 1));

        short i = l, j = r - (1 << lg);

        short mn = min(tbl[lg][i][0], tbl[lg][j][0]);
        short mx = max(tbl[lg][i][1], tbl[lg][j][1]);

        for(i += 1 << lg; i < j; i += 1 << lg) {
            mn = min(mn, tbl[lg][i][0]);
            mx = max(mx, tbl[lg][i][1]);
        }

        return {mn, mx};
    }

    bool built;
    short top;

    short N;
    vector<vector<array<short, 2>>> tbl;
};

struct SegTree {
    SegTree(short N): N(N) {
        st.reserve(2 * N); st.resize(2 * N);
    }

    void build(short v, const vector<array<short, 2>> &V) {
        short v0 = v;
        v += N;


        new (&st[v]) SparseTable(N - v0, v0, V);

        vector<array<short, 2>> A;
        A.reserve(N); A.resize(N);

        for(v >>= 1; v > 0; v >>= 1) {
            if(!st[v << 1].built || !st[v << 1 | 1].built) break;

            short b = st[v << 1].top, t = st[v << 1 | 1].top;

            bool swp = 0;
            if(b > t) swap(b, t), swp = 1;

            const short off = t - b + 1;

            fill(all(A), (array<short, 2>){SHRT_MAX, 0});

            short M = min(st[v << 1].N, st[v << 1 | 1].N);

            for(short i = 0; i < M; ++i) {
                short j, k; j = k = v << 1;

                (swp ? j : k)++;

                auto [x, y] = st[j].range_query(i, i + off);
                auto [a, b] = st[k].tbl[0][i];

                A[i] = {min(a, x), max(b, y)};
            }

            new (&st[v]) SparseTable(M, t, A);
        }
    }

    array<short, 2> query(short k, short v) {
        short l = k / 2, r = k;

        short s = SHRT_MAX, p = 0;
        for(l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if(l&1) {
                short off = 1 + k - st[l].top;

                auto [x, y] = st[l].range_query(v, v + off);

                s = min(s, x);
                p = max(p, y);

                l++;
            }
            if(r&1){
                r--;

                short off = 1 + k - st[r].top;

                auto [x, y] = st[r].range_query(v, v + off);

                s = min(s, x);
                p = max(p, y);
            }
        }

        return {s, p};
    }

    short N;
    vector<SparseTable> st;
};

int decorate(int N, vector<int> A) {
    A.shrink_to_fit();

    SegTree st(N);
    st.st[0].built = 1;

    map<int, short> mp;
    vector<int> B = A;
    sort(all(B));
    B.resize(unique(all(B)) - B.begin());

    for(short i = 0; i < B.size(); ++i)
        mp[B[i]] = i;

    vector<array<short, 2>> V;
    V.reserve(N); V.resize(N);

    for(short i = 0; i < N; ++i)
        V[i] = {mp[A[i]], mp[A[i]]};
    st.build(0, V);

    for(short k = 1; k < N - 1; ++k) {
        fill(all(V), (array<short, 2>){SHRT_MAX, 0});

        for(short i = 0; i + k < N; ++i) {
            auto [s, p] = st.query(k, i);

            V[i] = {p, s};
        }

        st.build(k, V);
    }

    auto [s, p] = st.query(N - 1, 0);

    return B[p];
}
