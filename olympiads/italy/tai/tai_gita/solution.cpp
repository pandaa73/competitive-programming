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

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

struct SegTree {
    static constexpr int N = 1 << 20;

    SegTree(void): T(2 * N) {}

    void point_add(int n, int x) {
        T[n += N] += x;

        for(n >>= 1; n > 0; n >>= 1) {
            T[n] = T[n << 1] + T[n << 1 | 1];
        }
    }

    int find_kth(int k) {
        int n = 1;
        for(; n < N; ) {
            n <<= 1;
            if(T[n] <= k) {
                k -= T[n];
                n |= 1;
            }
        }

        return n - N;
    }

    vec<int> T;
};

int visita(int N, vector<int> &A, vector<int> &B, vector<int> &D,
        vector<int> &C) {
    vec<int> E = D;
    sort(all(E));
    E.resize(unique(all(E)) - E.begin());

    for(auto &x: D) {
        x = lower_bound(all(E), x) - E.begin();
    }

    vec<vec<int>> adj(N);
    for(int e = 0; e < N - 1; ++e) {
        adj[A[e]].emplace_back(B[e]);
        adj[B[e]].emplace_back(A[e]);
    }

    SegTree st;
    vec<pii> dp(N, {0, N});
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        st.point_add(D[u], +1);

        for(auto v: adj[u]) {
            if(v == p) continue;

            dfs(v, u, dfs);

            dp[u].fi = max(dp[u].fi, dp[v].se);
            dp[u].se = min(dp[u].se, dp[v].fi);
        }

        if(adj[u].size() == 1 && p < N) {
            int x = st.find_kth(C[u]);
            dp[u] = {x, x};
        }

        st.point_add(D[u], -1);
    };

    dfs(0, N, dfs);

    return E[dp[0].fi];
}

#ifdef LOCAL

int main(){
	int N;
	cin >> N;
	vector<int> dolcezza(N), C(N), A(N - 1), B(N - 1);
	for (int i = 0; i < N; i++) {
		cin >> dolcezza[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> C[i];
	}
	for (int i = 0; i < N - 1; i++) {
		cin >> A[i] >> B[i];
	}
	cout << visita(N, A, B, dolcezza, C) << endl;
	return 0;
}

#endif /* LOCAL */
