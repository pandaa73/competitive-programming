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

constexpr int INF = 1e9;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    const int S = 0;
    const int T = 2 * N + 1;

    vector<int> ed; ed.reserve(6 * N);
    vector<vector<pii>> adj(2 * N + 2);
    auto add_edge = [&](int u, int v) {
        int i = ed.size();
        int j = i ^ 1;

        ed.emplace_back(1);
        ed.emplace_back(0);

        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, j);
    };

    for(int i = 1; i <= N; ++i) {
        add_edge(S, i);
        add_edge(N + i, T);
    }

    for(int i = 0; i < N; ++i) {
        int u, v; cin >> u >> v;
        v += N;

        add_edge(u, v);
    }

    vector<int> d(2 * N + 2);
    auto bfs = [&](void) -> bool {
        fill(all(d), -1); d[S] = 0;

        queue<int> q; q.emplace(S);
        while(!q.empty()) {
            auto v = q.front(); q.pop();

            for(auto [u, e]: adj[v]) {
                if(d[u] >= 0 || ed[e] == 0) continue;

                d[u] = 1 + d[v];
                q.emplace(u);
            }
        }

        return d[T] >= 0;
    };

    vector<int> nxt(2 * N + 2);
    auto dfs = [&](int v, int flow, auto &&dfs) -> int {
        if(v == T) return flow;

        for(int &id = nxt[v]; id < (int)adj[v].size(); ++id) {
            auto [u, e] = adj[v][id];

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

        while(int f = dfs(S, INF, dfs)) flow += f;
    }

    cout << flow << lf;
}
