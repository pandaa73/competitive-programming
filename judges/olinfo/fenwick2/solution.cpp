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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int add(int a, int b) {
    int x = a + b;

    return x < MOD ? x : x - MOD;
}

void chadd(int &a, int b) {
    a = add(a, b);
}

struct SegTree {
    SegTree(int N): N(N), T(2 * N) {}

    void point_add(int v, int x) {
        chadd(T[v += N], x);

        for(v >>= 1; v > 0; v >>= 1) {
            T[v] = add(T[v << 1], T[v << 1 | 1]);
        }
    }

    int range_sum(int l, int r) {
        int x = 0;

        for(l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if(l&1) chadd(x, T[l++]);
            if(r&1) chadd(x, T[--r]);
        }

        return x;
    }

    int N;
    vector<int> T;
};

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vector<int> V(N);
    for(auto &x: V) cin >> x;

    vector<int> W = V;

    sort(all(W));
    W.resize(unique(all(W)) - W.begin());

    for(int i = 0; i < N; ++i) {
        V[i] = lower_bound(all(W), V[i]) - W.begin();
    }

    int x = 0;

    SegTree st(N);
    for(int i = N - 1; i >= 0; i--) {
        int y = add(st.range_sum(V[i] + 1, N), 1);

        chadd(x, y);
        st.point_add(V[i], y);
    }

    cout << x << lf;
}
