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

constexpr int MOD = 676767677;

int add(int a, int b) {
    return a + b < MOD ? a + b : a + b - MOD;
}

void chadd(int &a, int b) {
    a = add(a, b);
}

int mul(int a, int b) {
    return (ll)a * b % MOD;
}

void chmul(int &a, int b) {
    a = mul(a, b);
}

struct Matrix {
    array<array<int, 5>, 5> data;

    Matrix(void): data({}) {}

    array<int, 5> &operator[](int i) { return data[i]; }
    const array<int, 5> &operator[](int i) const { return data[i]; }
};

Matrix mul(const Matrix &A, const Matrix &B) {
    Matrix C;
    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j) {
            for(int k = 0; k < 5; ++k) {
                chadd(C[i][j], mul(A[i][k], B[k][j]));
            }
        }
    }

    return C;
}

void chmul(Matrix &A, const Matrix &B) {
    A = mul(A, B);
}

Matrix fexp(Matrix B, ll e) {
    Matrix A;
    for(int i = 0; i < 5; ++i) {
        A[i][i] = 1;
    }

    for(; e > 0; e >>= 1, chmul(B, B)) {
        if(e&1) {
            chmul(A, B);
        }
    }

    return A;
}

array<Matrix, 8> MTX;

struct Node {
    Node(void): pri(timmy_loves_gambling()), l(0), r(0), k(0LL), sz(0LL), b(0) {
        for(int i = 0; i < 5; ++i) {
            m[i][i] = 1;
        }
    }

    Node(ll k, ll sz, int b): pri(timmy_loves_gambling()), l(0), r(0),
            k(k), sz(sz), b(b), m() {}

    int pri;
    int l, r;

    ll k, sz;

    int b;
    Matrix t;
    Matrix m;
};

vec<Node> T(1);

template<typename... Args>
int make_node(Args... args) {
    T.emplace_back(args...);
    return T.size() - 1;
}

int pull(int n) {
    int l = T[n].l, r = T[n].r;
    T[n].m = mul(mul(T[l].m, T[n].t), T[r].m);

    return n;
}

int merge(int l, int r) {
    if(!l || !r) return l ^ r;

    if(T[l].pri > T[r].pri) {
        T[l].r = merge(T[l].r, r);
        return pull(l);
    } else {
        T[r].l = merge(l, T[r].l);
        return pull(r);
    }
}

pii split(int n, ll k) {
    if(!n) return {};

    if(T[n].k < k) {
        auto [l, r] = split(T[n].r, k);
        T[n].r = l;
        return {pull(n), r};
    } else {
        auto [l, r] = split(T[n].l, k);
        T[n].l = r;
        return {l, pull(n)};
    }
}

ll prev(int n, ll k) {
    if(!n) return 0LL;

    if(T[n].k <= k) {
        return max(T[n].k, prev(T[n].r, k));
    } else {
        return prev(T[n].l, k);
    }
}

void calc(int n) {
    if(!n) return;

    T[n].m = T[n].t = mul(MTX[T[n].b], fexp(MTX[0], T[n].sz - 1));
}

int t = 0;

int inizia(long long N) {
    MTX[0].data[0][0] = MTX[0].data[0][1] = 1;
    MTX[0].data[1][1] = MTX[0].data[1][2]
        = MTX[0].data[1][3] = MTX[0].data[1][4] = 1;
    MTX[0].data[2][1] = MTX[0].data[2][2] = MTX[0].data[2][3] = 1;
    MTX[0].data[3][0] = MTX[0].data[3][1]
        = MTX[0].data[3][2] = MTX[0].data[3][3] = 1;
    MTX[0].data[4][3] = MTX[0].data[4][4] = 1;

    for(int b = 1; b < 8; ++b) {
        MTX[b] = MTX[0];

        for(int i = 0; i < 5; ++i) {
            MTX[b][0][i] = MTX[b][i][0] = 0;
            MTX[b][4][i] = MTX[b][i][4] = 0;

            if(b&1) {
                MTX[b][1][i] = MTX[b][i][1] = 0;
            }

            if(b&2) {
                MTX[b][2][i] = MTX[b][i][2] = 0;
                MTX[b][1][3] = MTX[b][3][1] = 0;
            }
            if(b&4) {
                MTX[b][3][i] = MTX[b][i][3] = 0;
            }
        }
    }

    t = make_node(0, N, 0);
    calc(t);

    return T[t].m[2][2];
}

int aggiorna(long long x, int y) {
    ll p = prev(t, x);

    auto [m, r] = split(t, p + 1);
    auto [l, n] = split(m, p);

    m = 0;

    if(T[n].k < x) {
        m = n;
        n = make_node(x, T[m].k + T[m].sz - x, 0);
        T[m].sz = x - T[m].k;
    }

    T[n].b ^= (1 << y);

    calc(m);
    calc(n);

    t = merge(l, merge(merge(m, n), r));

    return T[t].m[2][2];
}

#ifdef LOCAL

int main() {
    long long N;
    int Q;
    cin >> N >> Q;

    cout << inizia(N) << '\n';
    for (int i = 0; i < Q; i++) {
        long long x;
        int y;
        cin >> x >> y;

        cout << aggiorna(x, y) << '\n';
    }
}

#endif /* LOCAL */
