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

constexpr int INF = 1e9;

struct SegTree {
    SegTree(int N): N(N), T(2 * N, INF) {}

    void point_set(int n, int x) {
        T[n += N] = x;
        for(n >>= 1; n > 0; n >>= 1) {
            T[n] = min(T[n << 1], T[n << 1 | 1]);
        }
    }

    int range_min(int l, int r) {
        int x = INF;
        for(l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if(l&1) x = min(x, T[l++]);
            if(r&1) x = min(x, T[--r]);
        }

        return x;
    }

    int N;
    vec<int> T;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vec<int> A(N), B(N);
    for(auto &x: A) cin >> x;
    for(auto &x: B) cin >> x;

    SegTree st(N);
    st.point_set(N - 1, 0);
    for(int i = N - 2; i >= 0; i--) {
        if(B[i] >= 0) {
            st.point_set(i, st.T[N + B[i]]);
        } else {
            st.point_set(i, 1 + st.range_min(i + 1, i + A[i] + 1));
        }
    }

    cout << (st.T[N] >= INF ? -1 : st.T[N]) << lf;
}
