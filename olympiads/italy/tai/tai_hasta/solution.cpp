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

using pll = pair<int, int>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

#define L(v)   T[v].l
#define R(v)   T[v].r
#define sum(v) T[v].sum

struct SegTree {
    struct Node {
        int sum;
        int l, r;
    };

    SegTree(void): T(1), roots(1, 0) {}
    SegTree(int N): T(1), roots(1, 0) {
        T.reserve(N * LOG);
        roots.reserve(N + 1);
    }

    int make_node(void) {
        T.push_back({});
        return T.size() - 1;
    }

    int point_add(int v, int l, int r, int q, int x) {
        if(l > q || r <= q) return v;

        infof("... point_add(%d, %d, %d, %d, %d)", v, l, r, q, x);

        int nl = 0, nr = 0;
        int u = make_node();

        if(r - l != 1) {
            int m = (l + r) / 2;
            nl = point_add(L(v), l, m, q, x);
            nr = point_add(R(v), m, r, q, x);
        }

        sum(u) = sum(v) + x;
        L(u) = nl, R(u) = nr;

        infof("... ret u = %d: sum = %d | l = %d | r = %d",
            u, sum(u), L(u), R(u));

        return u;
    }

    int range_sum(int v, int l, int r, int ql, int qr) {
        if(l >= qr || r <= ql) return 0LL;

        infof("... range_sum(%d, %d, %d, %d, %d)", v, l, r, ql, qr);

        if(l >= ql && r <= qr) {
            infof("... ret sum = %d", sum(v));

            return sum(v);
        }

        int m = (l + r) / 2;
        int x = range_sum(L(v), l, m, ql, qr);
        int y = range_sum(R(v), m, r, ql, qr);

        infof("... ret sum = %d", x + y);

        return x + y;
    }

    vector<Node> T;
    vector<int> roots;
};

int N;
SegTree st;

void inizia(int N, int K, int V[], int R[]) {
    ::N = N;
    ::st = SegTree(N);

    vector<vector<int>> pos(K);
    for(int i = 0; i < N; ++i) {
        infof("======= i = %d =======", i);

        int k = V[i];
        int v = st.roots.back();

        pos[k].emplace_back(i);

        int j = pos[k].size() - R[k];

        if(j >= 0) {
            infof("----- add new -----");

            v = st.point_add(
                v,
                0, N,
                pos[k][j],
                R[k]
            );
        }

        if(j >= 1) {
            infof("----- rm old -----");

            v = st.point_add(
                v,
                0, N,
                pos[k][j - 1],
                -2 * R[k]
            );
        }

        if(j >= 2) {
            infof("----- add old -----");

            v = st.point_add(
                v,
                0, N,
                pos[k][j - 2],
                R[k]
            );
        }

        infof("root = %d", v);

        st.roots.emplace_back(v);
    }
}

int istiga(int l, int r) {
    ++r;

    infof("======= istiga(%d, %d) =======", l, r);

    return st.range_sum(
        st.roots[r],
        0, N,
        l, r
    );
}

#ifdef LOCAL
namespace {
    static FILE *fr, *fw;

    // Declaring variables
    static int N;
    static int K;
    static int i;
    static int j;
    static int Q;
    static int* V;
    static int* R;

    // Declaring functions
//    void inizia(int N,int K, int V[], int R[]);
//    int istiga(int i,int j);

    int sus() {
        fr = stdin;
        fw = stdout;

        // Reading input
        fscanf(fr,"%d %d",&N,&K);
        V = (int*)malloc((N) * sizeof(int));
        for (int i0 = 0; i0 < N; i0++) {
            fscanf(fr, " %d", &V[i0]);
        }
        R = (int*)malloc((K) * sizeof(int));
        for (int i0 = 0; i0 < K; i0++) {
            fscanf(fr, " %d", &R[i0]);
        }

        // Calling functions
        inizia(N,K,V,R);
        fscanf(fr,"%d",&Q);
        // Writing output
        while (Q--) {
            fscanf(fr,"%d %d",&i,&j);
            fprintf(fw,"%d ",istiga(i,j));
        }
        fprintf(fw,"\n");

        fclose(fr);
        fclose(fw);
        return 0;
    }
}

int main(void) {
    return ::sus();
}
#endif
