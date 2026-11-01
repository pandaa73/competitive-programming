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

constexpr int LOG = 30;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    const int S = N + 0;
    const int T = N + 1;

    vector<int> A(N), B(N);
    for(auto &x: A) cin >> x;
    for(auto &x: B) cin >> x;

    vector C(N, vector<int>(N));
    for(auto &v: C) for(auto &x: v) cin >> x;

    vector<vector<pii>> adj(N + 2);
    vector<ll> ed; ed.reserve(2 * N * (N + 2));
    auto push_edge = [&](int u, int v, int c) -> void {
        int i = ed.size();
        int j = i ^ 1;

        ed.emplace_back(c);
        ed.emplace_back(0);

        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, j);
    };

    for(int i = 0; i < N; ++i) {
        push_edge(S, i, A[i]);
        for(int j = 0; j < N; ++j) {
            push_edge(i, j, C[i][j]);
        }

        push_edge(i, T, B[i]);
    }

    ll scale;

    vector<int> d(N + 2);
    auto bfs = [&](void) -> bool {
        fill(all(d), -1); d[S] = 0;

        queue<int> q; q.emplace(S);
        while(!q.empty()) {
            int v = q.front(); q.pop();

            for(auto [u, e]: adj[v]) {
                if(d[u] >= 0 || ed[e] < scale) continue;

                d[u] = 1 + d[v];
                q.emplace(u);
            }
        }

        return d[T] >= 0;
    };

    vector<int> nxt(N + 2);
    auto dfs = [&](int v, ll flow, auto &&dfs) -> ll {
        if(v == T) return flow;

        for(; nxt[v] < adj[v].size(); ++nxt[v]) {
            auto [u, e] = adj[v][nxt[v]];

            if(d[u] <= d[v] || ed[e] < scale) continue;

            ll f = dfs(u, min(flow, ed[e]), dfs);

            if(f == 0) continue;

            ed[e ^ 0] -= f;
            ed[e ^ 1] += f;

            return f;
        }

        return 0;
    };

    ll flow = 0;
    for(int lg = LOG; lg >= 0; lg--) {
        scale = 1LL << lg;

        while(bfs()) {
            fill(all(nxt), 0);

            while(ll f = dfs(S, LLONG_MAX, dfs)) flow += f;
        }
    }

    cout << flow << lf;
}
