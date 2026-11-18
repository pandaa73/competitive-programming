#include <bits/stdc++.h>
using namespace std;

#include <cassert>

#define lf "\n"
#define ff endl
#define fi first
#define se second
#define _ << " " <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#ifdef DEBUG

constexpr bool IS_DEBUG = true;

#define infor(fmt, ...) do { print(stderr, fmt, ##__VA_ARGS__); } while(0)
#define infof(fmt, ...) do { print(stderr, fmt, ##__VA_ARGS__); } while(0)

#else

constexpr bool IS_DEBUG = false;

#define infor(fmt, ...)
#define infof(fmt, ...)

#endif /* DEBUG */

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

constexpr ll INF = 1e18+7;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M, K; cin >> N >> M >> K;
    int L, U, V; cin >> L >> U >> V;

    vec<int> X(M), Y(M), Z(M);
    for(auto &x: X) cin >> x;
    for(auto &x: Y) cin >> x;
    for(auto &x: Z) cin >> x;

    vec<ll> T(K);
    for(auto &x: T) cin >> x;

    sort(all(T));

    vec<int> P(L);
    for(auto &x: P) cin >> x;

    vec<vec<pii>> adj(N);
    for(int e = 0; e < M; ++e) {
        int u = X[e];
        int v = Y[e];
        int w = Z[e];

        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    vec<ll> pd(N, INF);
    vec<bool> is_path(N, false);
    for(auto n: P) {
        is_path[n] = true;
    }

    pd[P[0]] = 0;
    for(int i = 1; i < L; ++i) {
        int uu = P[i], vv = P[i - 1], ww = -1;
        for(auto [v, w]: adj[uu]) {
            if(v == vv) ww = w;
        }

        while(ww < -1) cout << 1 << lf;

        pd[uu] = pd[vv] + (ll)V * ww;
    }

    vec<ll> d(N, INF);
    priority_queue<pll, vec<pll>, greater<pll>> q;

    d[0] = 0;
    q.emplace(0, 0);

    while(!q.empty()) {
        auto [l, u] = q.top();
        q.pop();

        if(l != d[u]) continue;

        if(u == N - 1) {
            cout << l << lf;
            return 0;
        }

        for(auto [v, w]: adj[u]) {
            ll nl = l + (ll)U * w;

            if(K > 0 && is_path[u] && is_path[v] && pd[u] < pd[v]) {
                auto it = lower_bound(all(T), l - pd[u]);
                if(it != T.begin()) {
                    ll t = *prev(it);
                    nl = max(nl, t + pd[v]);
                }
            }

            if(nl < d[v]) {
                d[v] = nl;
                q.emplace(nl, v);
            }
        }
    }

    while(true) cout << 1 << lf;
}
