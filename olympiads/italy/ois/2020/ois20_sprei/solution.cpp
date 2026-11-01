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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

#define in(v) (v << 1)
#define out(v) (v << 1 | 1)

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M, B; cin >> N >> M >> B;
    map<vector<int>, int> m;

    const int S = N + 0;
    const int T = N + 1;

    vector<int> s(N);
    for(int i = 0; i < N; ++i) {
        vector<int> P(M);
        for(auto &x: P) cin >> x;

        m[P] = i;
        s[i] = accumulate(all(P), 0LL)&1;
    }

    vector<pii> edges;
    for(auto &[P, i]: m) {
        auto Q = P;
        for(int j = 0; j < M; ++j) {
            Q[j] += 1;
            auto it = m.find(Q);
            Q[j] -= 1;

            if(it == m.end()) continue;

            if(s[i]) {
                edges.emplace_back(it->se, i);
            } else edges.emplace_back(i, it->se);
        }
    }

    vector<vector<pii>> adj(N + 2);
    vector<int> ed; ed.reserve(2 * edges.size() + 2 * N);
    auto push_edge = [&](int u, int v) -> void {
        int i = ed.size();
        int j = i ^ 1;

        ed.emplace_back(1);
        ed.emplace_back(0);

        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, j);
    };

    for(auto [u, v]: edges) {
        push_edge(u, v);
    }

    for(int i = 0; i < N; ++i) {
        if(s[i]) {
            push_edge(i, T);
        } else push_edge(S, i);
    }

    vector<int> d(N + 2);
    auto bfs = [&](void) -> bool {
        fill(all(d), -1); d[S] = 0;

        queue<int> q; q.emplace(S);
        while(!q.empty()) {
            auto v = q.front(); q.pop();

            for(auto [u, e]: adj[v]) {
                if(d[u] >= 0 || ed[e] == 0) continue;

                q.emplace(u);
                d[u] = 1 + d[v];
            }
        }

        return d[T] >= 0;
    };

    vector<int> nxt(N + 2);
    auto dfs = [&](int v, int flow, auto &&dfs) -> int {
        if(v == T) return flow;

        for(; nxt[v] < adj[v].size(); ++nxt[v]) {
            auto [u, e] = adj[v][nxt[v]];

            if(d[u] <= d[v] || ed[e] == 0) continue;

            int f = dfs(u, min(flow, ed[e]), dfs);

            if(f == 0) continue;

            ed[e ^ 0] -= f;
            ed[e ^ 1] += f;

            return f;
        }

        return 0;
    };

    int flow = 0;
    while(bfs()) {
        fill(all(nxt), 0);

        while(int f = dfs(S, INT_MAX, dfs)) flow += f;
    }

    cout << flow << lf;
}
